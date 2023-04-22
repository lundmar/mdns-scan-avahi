# mdns-scan-avahi

A simple mDNS scanner with only lists the most useful information in a concise
way. It is similar to mdns-scan but implemented using the Avahi mDNS backend.

## Usage

```
$ mdns-scan-avahi
switch2b370c                               192.168.0.120                   port 80     type _http._tcp
switch2b370c                               192.168.0.120                   port 80     type _http._tcp
switch2b370c                               192.168.0.120                   port 80     type _http._tcp
switch2b370c                               192.168.0.120                   port 80     type _http._tcp
Philips Hue - 93E705                       192.168.0.177                   port 443    type _hue._tcp
Philips Hue - 93E705                       192.168.0.177                   port 443    type _hue._tcp
Philips Hue - 93E705                       192.168.0.177                   port 443    type _hue._tcp
Philips Hue - 93E705                       192.168.0.177                   port 443    type _hue._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 9100   type _pdl-datastream._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 9100   type _pdl-datastream._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 515    type _printer._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 515    type _printer._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 631    type _ipp._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 631    type _ipp._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 54921  type _scanner._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 54921  type _scanner._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _http._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _http._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _uscan._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _uscan._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 9100   type _pdl-datastream._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 9100   type _pdl-datastream._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 515    type _printer._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 515    type _printer._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 631    type _ipp._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 631    type _ipp._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 54921  type _scanner._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 54921  type _scanner._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _http._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _http._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _uscan._tcp
Brother MFC-L2730DW series                 192.168.0.188                   port 80     type _uscan._tcp
```

## Installation

### Installation from source

The latest source releases can be found [here](https://github.com/lundmar/mdns-scan-avahi/releases).

Install steps:
```
$ meson build
$ meson compile -C build
$ meson install -C build
```

Note: The meson install steps may differ depending on your specific system.

