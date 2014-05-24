////////////////////////////////////////////////////////////////////////////////
// Author: Nick Vrvilo (nick.vrvilo@rice.edu)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// item collection declarations

[ int *above ];    // Last row of tile above
[ int *left  ];    // Last column of tile to the left
[ SeqData *data ]; // Static data for the sequences and tile sizes
[ struct timeval *startTime ]; // Only used for timing the computation

////////////////////////////////////////////////////////////////////////////////
// Control tags and steps

< int [2] swTag > ;  
< int [2] initAboveTag > ;  
< int [2] initLeftTag > ;  

< swTag > :: ( swStep ) ;	
< initAboveTag > :: ( initAboveStep ) ;	
< initLeftTag > :: ( initLeftStep ) ;	

////////////////////////////////////////////////////////////////////////////////
// Input output relationships

( initAboveStep: tw, ntw ) -> [ above: 0, {0..ntw} ];

( initLeftStep:  th, nth ) -> [ left:  {0..nth}, 0 ];

[ data: 0 ],
[ above: i, j ], [ left: i, j ]
-> ( swStep: i, j ) ->
[ above: i+1, j ], [ left: i, j+1 ];

// Write graph inputs and start steps
env -> [ startTime: 0 ];
env -> < initAboveTag: tw, ntw >, < initLeftTag: th, nth >;
env -> < swTag: {0..ntw}, {0..nth} >;

// Return outputs to the caller
[ startTime: 0 ], [ above: nth, ntw-1 ] -> ( env: ntw, nth, tw );

