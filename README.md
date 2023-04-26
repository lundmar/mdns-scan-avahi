# mdns-scan-avahi

## Introduction
A simple mDNS scanner which only lists the most useful device information. It is
similar to mdns-scan but implemented using the Avahi mDNS backend.

## Motivation

Author needed to quickly identify new devices on a network, in particular the IP
and port of newly added devices. The avahi-browse tool can be used for that but
its output is quite noisy and hard to read. Hence the creation of this tool.

## Usage

```
$ mdns-scan-avahi
switch2b370c                       192.168.0.120         port 80     type _http._tcp
switch2b370c                       192.168.0.120         port 80     type _http._tcp
Philips Hue - 93E705               192.168.0.177         port 443    type _hue._tcp
Brother MFC-L2730DW series         192.168.0.188         port 9100   type _pdl-datastream._tcp
Brother MFC-L2730DW series         192.168.0.188         port 515    type _printer._tcp
Brother MFC-L2730DW series         192.168.0.188         port 631    type _ipp._tcp
Brother MFC-L2730DW series         192.168.0.188         port 54921  type _scanner._tcp
Brother MFC-L2730DW series         192.168.0.188         port 80     type _http._tcp
Brother MFC-L2730DW series         192.168.0.188         port 80     type _uscan._tcp
Brother MFC-L2730DW series         192.168.0.188         port 9100   type _pdl-datastream._tcp
Brother MFC-L2730DW series         192.168.0.188         port 515    type _printer._tcp
Brother MFC-L2730DW series         192.168.0.188         port 631    type _ipp._tcp
Brother MFC-L2730DW series         192.168.0.188         port 54921  type _scanner._tcp
Brother MFC-L2730DW series         192.168.0.188         port 80     type _http._tcp
Brother MFC-L2730DW series         192.168.0.188         port 80     type _uscan._tcp
Scanning.. /
```

## Installation

### Installation from source

First make sure you have libavahi-client-dev installed.

Install steps:
```
$ meson setup build
$ meson compile -C build
$ meson install -C build
```

Note: The meson install steps may differ depending on your specific system.

Note: To install in home directory, do e.g.:
```
$ meson setup build --prefix=$HOME/opt/mdns-scan-avahi
```

