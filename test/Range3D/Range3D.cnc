[ int data: i, j, k, l ];
[ int sum: () ];

( $init: () ) -> [ data: {0..5}, {0..5}, {0..5}, {0..5} ], ( summing: () );
( summing: () ) <- [ data: {0..2}, {0..5}, 2, {4..5} ] -> [ sum: () ];
( $finalize: () ) <- [ sum: () ];
