////////////////////////////////////////////////////////////////////////////////
// Author: Nick Vrvilo (nick.vrvilo@rice.edu)
////////////////////////////////////////////////////////////////////////////////

$context {
    int tw, th, ntw, nth;
    int dataSize;
};

////////////////////////////////////////////////////////////////////////////////
// item collection declarations

[ int *above : i, j ];    // Last row of tile above
[ int *left  : i, j ];    // Last column of tile to the left

////////////////////////////////////////////////////////////////////////////////
// Input output relationships

( initAboveStep: tw, ntw ) -> [ above: 0, {0..ntw} ];

( initLeftStep:  th, nth ) -> [ left:  {0..nth}, 0 ];

( swStep: i, j )
    <- [ above: i, j ], [ left: i, j ]
    -> [ below @ above: i+1, j ], [ right @ left: i, j+1 ];

// Write graph inputs and start steps
( $init: ntw, nth, tw, th )
    -> [ startTime: () ],
       ( initAboveStep: tw, ntw ),
       ( initLeftStep: th, nth ),
       ( swStep: {0..nth}, {0..ntw} );

( $finalize: ntw, nth, tw ) <- [ above: nth, ntw-1 ];
