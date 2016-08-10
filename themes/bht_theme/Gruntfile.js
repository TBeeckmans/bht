module.exports = function(grunt) {
  "use strict";

  var neat = require('node-neat').includePaths;

  // 1. All configuration goes here
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    concat: {
      dist: {
        src: [
          // All JS in the libs folder
          'js/jquery.flexslider-min.js',
          // 'js/jquery.fitvids-min.js',
          'js/jquery.colorbox-min.js',
          'js/jquery.scrollto.min.js',
          'js/scripts.js',
          'js/respond.js',
        ],
        dest: 'js/production.js',
      }
    },

    uglify: {
      build: {
        src: 'js/production.js',
        dest: 'js/production.min.js'
      }
    },

    tinypng: {
      options: {
        apiKey: "ktZFxRLuPDsRp28RiCX8nsZPPuJiG0Ju",
        // apiKey: "E0HQ7_hk7TEL3OLzWOKoFYOLUjiUZhLH",
        summarize: true,
        showProgress: true,
        expand: true,
      },
      compress: {
        expand: true,
        src: 'img/*.png',
        dest: '',
        ext: '.png'
      },
    },

    imagemin: {
      dynamic: {
        files: [{
          expand: true,
          cwd: 'img-src/',
          src: ['**/*.{png,jpg,gif}'],
          dest: 'img/'
        }]
      }
    },

    sass: {
      options: {
        spawn: false,
        includePaths: neat,
        outputStyle: 'nested' // libsass doesn't yet support these: expanded / compressed
      },
      dist: {
        files: {
          'css/style.css': 'scss/style.scss',
          'css/styleguide.css': 'scss/styleguide.scss',
        },
        options: {
          sourceMap: 'css/style.css.map',
          sourceMapContents: true
        }
      },
      prod: {
        files: {
          'css/style.css': 'scss/style.scss',
          'css/styleguide.css': 'scss/styleguide.scss',
        },
        options: {
          // outputStyle: 'compressed' // libsass doesn't yet support compressed
        }
      }
    },

    watch: {
      options: {
        livereload: true,
      },
      scripts: {
        files: ['js/*.js'],
        // tasks: ['concat', 'uglify'],
        options: {
          spawn: false,
        },
      },
      templates: {
        files: ['templates/*.tpl.php', 'templates/*/*.tpl.php'],
        options: {
          spawn: false,
        },
      },
      colors: {
        files: ['colors.json'],
        tasks: ['shared_config', 'sass:dist'],
        options: {
          spawn: true,
        }
      },
      css: {
        files: ['scss/*.scss', 'scss/*/*.scss', 'scss/*/*/*.scss', '!scss/components/_colors.scss', '!scss/components/icon-*.scss'],
        tasks: ['sass:dist'],
        options: {
          spawn: false,
        }
      }
    },

    clean: {
      options: {
        'no-write': false,
      },
      iconizr: {
        src: [
          './img-src/**/styled/*.svg',
          './img/icon-loader-fragment.html',
          './img/separates.png', './img/separates.svg',
          './scss/components/icon-png-data.scss',
          './scss/components/icon-png-sprite.scss',
          './scss/components/icon-svg-data.scss'
        ]
      },
      prod: {
        src: ['./css/*.css.map']
      }
    },

    replace: {
      options: {
        patterns: [
          {
            json: grunt.file.readJSON('colors.json')
          }
        ]
      },
      svg_colors: {
        files: [
          {
            expand: true,
            flatten: true,
            src: 'colors-svg.json',
            dest: './img-src/',
          }
        ]
      },
      svg: {
        options: {
          patterns: [
            {
              json: grunt.file.readJSON('img-src/colors-svg.json')
            }
          ]
        },
        files: [
          {
            expand: true,
            flatten: true,
            src: './img-src/*.svg',
            dest: './img-src/styled/',
          }
        ]
      },
      icon: {
        options: {
          patterns: [
            {
              json: grunt.file.readJSON('img-src/colors-svg.json')
            }
          ]
        },
        files: [
          {
            expand: true,
            flatten: true,
            src: './img-src/icon/*.svg',
            dest: './img-src/icon/styled/',
          }
        ]
      }
    },

    iconizr: {
      options: {
        // Task-specific options go here.
      },
      separates: {
        // Target specific file lists
        src            : 'img-src/styled',
        dest           : 'img',

        // Target specific options
        options        : {
          // Rendering configuration (output formats like CSS, Sass, etc.)
          render       : {
            // Disable HTML rendering
            html       : false,
            // Disable CSS rendering
            css        : false,
            // Disable Sass rendering
            scss       : false,
          },
          // Sprite subdirectory name ["svg"]
          spritedir    : '',
          // Sprite file name ["sprite"]
          sprite       : 'separates',
          // Keep intermediate SVG files (inside sprite subdirectory) [false]
          keep         : true,
          // Recursive scan of the input directory for SVG files [false]
          recursive    : false,
          // Output verbose progress information (0-3) [0]
          verbose      : 3,
          // Module to be used for SVG cleaning. ["svgo"] ("scour" or "svgo")
          cleanwith    : 'svgo',
          // Configuration options for the cleaning module [{}]
          cleanconfig  : {
            plugins: [{},]
          },
          // Whether to quantize the PNG images (convert to 8-bit) [false]
          quantize     : false,
          // PNG image optimization level (0-11) [3]
          level        : 3
        },
      },
      spritesheet: {
        // Target specific file lists
        src            : 'img-src/icon/styled',
        dest           : 'img',

        // Target specific options
        options        : {
          // Rendering configuration (output formats like CSS, Sass, etc.)
          render       : {
            // Disable HTML rendering
            html       : false,
            // Disable CSS rendering
            css        : false,
            // Activate Sass rendering
            scss       : {
              template : 'mustache/sprite.scss',
              dest     : '../scss/components/icon'
            }
          },
          // Custom Mustache rendering variables [{}]
          variables    : {
            'filename' : {
              'png'    : 'spritesheet.png',
              'svg'    : 'spritesheet.svg',
            }
          },
          // Sprite subdirectory name ["svg"]
          spritedir    : '',
          // Sprite file name ["sprite"]
          sprite       : 'spritesheet',
          // CSS selector prefix ["svg"]
          prefix       : 'icon',
          // Common CSS selector for all images [empty]
          common       : 'icon',
          // Maximum single image width [1000]
          maxwidth     : 1000,
          // Maximum single image height [1000]
          maxheight    : 2000,
          // Transparent padding around the single images (in pixel) [0]
          padding      : 0,
          // Image arrangement within the sprite ["vertical"]
          // ("vertical", "horizontal" or "diagonal")
          layout       : 'vertical',
          // Character sequence for denoting CSS pseudo classes ["~"]
          pseudo       : '~',
          // Render image dimensions as separate CSS rules [false]
          dims         : true,
          // Keep intermediate SVG files (inside sprite subdirectory) [false]
          keep         : false,
          // Recursive scan of the input directory for SVG files [false]
          recursive    : true,
          // Output verbose progress information (0-3) [0]
          verbose      : 1,
          // Module to be used for SVG cleaning. ["svgo"] ("scour" or "svgo")
          cleanwith    : 'svgo',
          // Configuration options for the cleaning module [{}]
          cleanconfig  : {
            plugins: [{}, ]
          },
          // Whether to quantize the PNG images (convert to 8-bit) [false]
          quantize     : false,
          // PNG image optimization level (0-11) [3]
          level        : 3,
          // Embed path for the HTML loader fragment [empty]
          // embed        : false,
          // Maximum data URI size for SVG embedding [1048576]
          svg          : 1048576,
          // Maximum data URI size for PNG embedding [32768]
          png          : 32768,
          // Relative directory path used for preview document rendering [empty]
          preview      : ''
        },
      },
    },

    penthouse: {
      extract : {
        outfile : 'css/critical.css',
        css : 'css/style.css',
        url : 'http://bht.dev/',
        width : 1300,
        height : 900
      }
    },

    cssmin: {
      combine: {
        files: {
          'css/critical.min.css': 'css/critical.css',
          'css/style.min.css': 'css/style.css',
          'css/fonts.min.css': 'css/fonts.css',
          // 'path/to/output.css': ['path/to/input_one.css', 'path/to/input_two.css']
        }
      }
    },

    shared_config: {
      dist: {
        options: {
          'name': 'colorConfig',
          'cssFormat': 'dash'
        },
        src: 'colors.json',
        dest: [
          'scss/components/_colors.scss'
        ]
      }
    }

  });

  // 3. Where we tell Grunt we plan to use this plug-in.
  grunt.loadNpmTasks('grunt-sass'); //C-versie: http://benfrain.com/lightning-fast-sass-compiling-with-libsass-node-sass-and-grunt-sass/
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-cssmin');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-imagemin');
  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.loadNpmTasks('grunt-shared-config');
  grunt.loadNpmTasks('grunt-replace');
  // grunt.loadNpmTasks('grunt-iconizr');
  grunt.loadNpmTasks('grunt-tinypng');
  grunt.loadNpmTasks('grunt-penthouse');

  // 4. Where we tell Grunt what to do when we type "grunt" into the terminal.

  // > grunt
  grunt.registerTask('default', [
    'sass:dist',
    'watch'
  ]);

  // > grunt images
  grunt.registerTask('images', [
    // 'clean:iconizr',
    // 'replace:svg_colors',
    // 'replace:svg',
    // 'iconizr:separates',
    'imagemin',
    // 'clean:iconizr',
    'sass:dist'
  ]);

  // > grunt sprites
  // grunt.registerTask('sprites', [
  //   'clean:iconizr',
  //   'replace:svg_colors',
  //   'replace:icon',
  //   'iconizr:spritesheet',
  //   'clean:iconizr',
  //   'sass:dist'
  // ]);

  // > grunt production
  grunt.registerTask('production', [
    'concat',
    'uglify',
    'clean',
    'shared_config',
    'tinypng',
    'sass:prod',
    'penthouse',
    'cssmin'
  ]);

};
