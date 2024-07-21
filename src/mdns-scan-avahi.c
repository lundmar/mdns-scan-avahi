/* SPDX-License-Identifier: LGPL-2.1-or-later */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <net/if.h>
#include <pthread.h>
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/malloc.h>
#include <avahi-common/error.h>

pthread_t print_thread;
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

static AvahiSimplePoll *simple_poll = NULL;

void *thread_scan_spinner_function(void *dummyPtr)
{
    int counter = 0;
    while (1)
    {
        usleep(500000);
        pthread_mutex_lock(&print_mutex);
        printf("Scanning..  ");
        printf("\b%c", "|/-\\"[counter++]);
        printf("\r");
        if (counter == 4)
        {
            counter = 0;
        }
        fflush(stdout);
        pthread_mutex_unlock(&print_mutex);
    }
    return NULL;
}

static void resolve_callback(
    AvahiServiceResolver *r,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *address,
    uint16_t port,
    AvahiStringList *txt,
    AvahiLookupResultFlags flags,
    AVAHI_GCC_UNUSED void* userdata)
{
    assert(r);

    /* Called whenever a service has been resolved successfully or timed out */

    switch (event)
    {
        case AVAHI_RESOLVER_FAILURE:
            break;

        case AVAHI_RESOLVER_FOUND:
            {
                char a[AVAHI_ADDRESS_STR_MAX], *t;

                avahi_address_snprint(a, sizeof(a), address);
                t = avahi_string_list_to_string(txt);
                pthread_mutex_lock(&print_mutex);
                printf("%-42s %-30s  port %-6u type %s\n" , name, a, port, type);
                pthread_mutex_unlock(&print_mutex);

                avahi_free(t);
            }
    }

    avahi_service_resolver_free(r);
}

static void service_browser_callback(
    AvahiServiceBrowser *b,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *name,
    const char *type,
    const char *domain,
    AvahiLookupResultFlags flags,
    void *userdata)
{
    AvahiClient *client = userdata;

    assert(b);

    switch (event)
    {
        case AVAHI_BROWSER_NEW:
            if (!(avahi_service_resolver_new(client, interface, protocol, name, type, domain, AVAHI_PROTO_UNSPEC, 0, resolve_callback, client)))
            {
                fprintf(stderr, "Failed to resolve service '%s': %s\n", name, avahi_strerror(avahi_client_errno(client)));
            }
            break;

        case AVAHI_BROWSER_REMOVE: 
            break;

        case AVAHI_BROWSER_FAILURE:
            fprintf(stderr, "service_browser failed: %s\n", avahi_strerror(avahi_client_errno(client)));
            avahi_simple_poll_quit(simple_poll);
            break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
            break;
    }
}

static void browse_service_type(const char *stype, const char *domain, AvahiClient *client)
{
    AvahiServiceBrowser *b;

    assert(client);
    assert(stype);

    if (!(b = avahi_service_browser_new(
              client,
              AVAHI_IF_UNSPEC,
              AVAHI_PROTO_UNSPEC,
              stype,
              domain,
              0,
              service_browser_callback,
              client)))
    {
        fprintf(stderr, "avahi_service_browser_new() failed: %s\n", avahi_strerror(avahi_client_errno(client)));
        avahi_simple_poll_quit(simple_poll);
    }
}

static void service_type_browser_callback(
    AvahiServiceTypeBrowser *b,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *type,
    const char *domain,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void *userdata)
{

    AvahiClient *client = userdata;
    assert(client);
    assert(b);

    switch (event)
    {

        case AVAHI_BROWSER_NEW:
            browse_service_type(type, domain, client);
            break;

        case AVAHI_BROWSER_REMOVE:
            /* We're dirty and never remove the browser again */
            break;

        case AVAHI_BROWSER_FAILURE:
            break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
            break;
    }
}

static void client_callback(AvahiClient *c, AvahiClientState state, AVAHI_GCC_UNUSED void * userdata)
{
    assert(c);

    /* Called whenever the client or server state changes */
    if (state == AVAHI_CLIENT_FAILURE)
    {
        fprintf(stderr, "Server connection failure: %s\n", avahi_strerror(avahi_client_errno(c)));
        avahi_simple_poll_quit(simple_poll);
    }
}

int main(AVAHI_GCC_UNUSED int argc, AVAHI_GCC_UNUSED char*argv[])
{
    AvahiServiceTypeBrowser *sb = NULL;
    AvahiClient *client = NULL;
    int error;
    int ret = 1;

    /* Allocate main loop object */
    if (!(simple_poll = avahi_simple_poll_new()))
    {
        fprintf(stderr, "Failed to create simple poll object.\n");
        goto fail;
    }

    /* Allocate a new client */
    client = avahi_client_new(avahi_simple_poll_get(simple_poll), 0, client_callback, NULL, &error);

    /* Check whether creating the client object succeeded */
    if (!client)
    {
        fprintf(stderr, "Failed to create client: %s\n", avahi_strerror(error));
        goto fail;
    }

    /* Create the service browser */
    if (!(sb = avahi_service_type_browser_new(client, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, "local", 0, service_type_browser_callback, client)))
    {
        fprintf(stderr, "Failed to create service browser: %s\n", avahi_strerror(avahi_client_errno(client)));
        goto fail;
    }

    pthread_create(&print_thread, NULL, thread_scan_spinner_function, NULL);

    /* Run the main loop */
    avahi_simple_poll_loop(simple_poll);

    ret = 0;

fail:

    /* Cleanup */
    if (sb)
        avahi_service_type_browser_free(sb);

    if (client)
        avahi_client_free(client);

    if (simple_poll)
        avahi_simple_poll_free(simple_poll);

    return ret;
}
