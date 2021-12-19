<?php

// live
// Server
$env_live = 'belgianhandtherapists.be';
// User
$remote_user_live = 'belgianhandtherapistsbe';

// Alias
$aliases['bht.live'] = [
  'root' => '/www/bht/docroot',
  'path-aliases' => [
    '%dump' => sprintf('/tmp/sql-sync-live-%s-local.sql', 'bht'),
  ],
  'command-specific' => [
    'core-rsync' => [
      'mode' => 'rlvz',
      'chmod' => 'ugo=rwX',
      'perms' => TRUE,
    ],
    'rsync' => [
      'mode' => 'rlvz',
      'chmod' => 'ugo=rwX',
      'perms' => TRUE,
    ],
  ],
  'target-command-specific' => [
    'sql-sync' => [
      'no-ordered-dump' => TRUE,
    ],
  ],
];


