{
  'targets': [
    {
      'target_name': 'libtorrent',
      'sources': [
        'src/add_torrent_params.cc',
        'src/alert.cc',
        'src/alert_types.cc',
        'src/libtorrent.cc',
        'src/session.cc',
        'src/torrent_info.cc',
        'src/torrent_handle.cc',
        'src/torrent_status.cc'
      ],
      'include_dirs': [
        'C:/Libs/libtorrent-rasterbar-1.0.3/build/release/include',
        'C:/Libs/boost_1_57_0'
      ],
      'link_settings': {
        'libraries': [
          '-llibtorrent'
        ]
      },
      'library_dirs': [
        'C:/Libs/boost_1_57_0/stage/lib',
        'C:/Libs/libtorrent-rasterbar-1.0.3/build/release/lib'
      ],
      'defines': [
        'BOOST_ASIO_SEPARATE_COMPILATION'
      ],
      'conditions': [
        ['OS=="win"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': [
                '/EHcs',
                '/MP'
              ]
            }
          }
        }]
      ]
    },
    {
      'target_name': 'action_after_build',
      'type': 'none',
      'dependencies': ['<(module_name)'],
      'copies': [
        {
          'files': ['<(PRODUCT_DIR)/<(module_name).node'],
          'destination': '<(module_path)'
        }
      ]
    }
  ]
}