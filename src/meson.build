config_h = configuration_data()
config_h.set_quoted('VERSION', meson.project_version())
configure_file(output: 'config.h', configuration: config_h)

# mdns-scan-avahi application
mdns_scan_avahi_sources = [
  'mdns-scan-avahi.c',
]

mdns_scan_avahi_c_args = ['-Wno-unused-result', '-Wno-unused-parameter']

mdns_scan_avahi_dep = [
  dependency('avahi-client', required: true),
]

executable('mdns-scan-avahi',
  mdns_scan_avahi_sources,
  c_args: mdns_scan_avahi_c_args,
  dependencies: mdns_scan_avahi_dep,
  install: true )

