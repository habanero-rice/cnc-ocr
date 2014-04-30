////////////////////////////////////////////////////////////////////////////////
// Alina Sbirlea - alina@rice.edu
// Adapted for CnC-HC after Sagnak Tasirlar's Cholesky for HJ-CNC
// influenced by Aparna Chandramowlishwaran's Intel CnC C++ implementation
// and by Zoran Budimlic's Habanero CnC Java implementation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// item collection declarations

[ int numTiles ];
[ int tileSize ];

[ double *Lkji ];           // The input/intermediate matrix tiles
[ double *results ];        // The result matrix tiles

[ struct timeval *startTime ]; // Only used for timing the computation

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// tags declarations (comments are Aparna's )

< int [1] singletonTag >;
< int [1] controlS1Tag >;    // Tag values are indices of Step 1 [k = 0...p-1]
< int [2] controlS2Tag >;    // Tag values are indices of Step 2 [j = k+1...p-1]
< int [3] controlS3Tag >;    // Tag values are indices of Step 3 [i = k+1...j]
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Step Prescriptions

//< singletonTag > :: ( kComputeStep ); //start directly with kComputeStep

< controlS1Tag > :: ( kjComputeStep ), ( s1ComputeStep );
< controlS2Tag > :: ( kjiComputeStep ), ( s2ComputeStep );
< controlS3Tag > :: ( s3ComputeStep );
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Input output relationships (comments are Aparna's )
//
// The kComputeStep produces 'k' loop indices (in the form of tag instance )
[ numTiles: 0 ] -> ( kComputeStep: k ) -> < controlS1Tag: { 0 .. numTiles[0] } >;

// The kjCompute step produces 'j' loop indices (in the form of tag instance )
[ numTiles: 0 ] -> ( kjComputeStep: k ) -> < controlS2Tag: k, { k+1 .. numTiles[0] } >;

// The kjiComputeStep produces 'i' loop indices (in the form of tag instance )
( kjiComputeStep: k, j ) -> < controlS3Tag: k, j, { k+1 .. j+1 } >;

// Step 1 Executions
[ tileSize: 0 ], [ Lkji: k, k, k ] -> ( s1ComputeStep: k ) -> [ Lkji: k, k, k+1 ];
 
// Step 2 Executions
[ tileSize: 0 ], [ Lkji: j, k, k ], [ Lkji: k, k, k+1 ] -> ( s2ComputeStep: k, j ) -> [ Lkji: j, k, k+1 ];

// Step 3 Executions
[ tileSize: 0 ], [ Lkji: j, i, k ], [ Lkji: j, k, k+1 ], [ Lkji: i, k, k+1 ] -> ( s3ComputeStep: k, j, i ) -> [ Lkji: j, i, k+1 ];

// Input from the caller: tile pointers, tile size and loop end value
//env -> [ Lkji ], [ tileSize ], [ numTiles ], < singletonTag >;
 
// Return to the caller
// NOTE: tileCount is the total number of result tiles;
//       numTiles is the number of tiles in the first column of the matrix.
[ startTime: 0], [ numTiles: 0 ], [ tileSize: 0 ], [ results: {0..tileCount} ] -> ( env: tileCount );

// NOTE:
// j = matrix tile's row
// i = matrix tile's column
// k = iteration number (up to i+1)
