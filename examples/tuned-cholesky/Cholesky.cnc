////////////////////////////////////////////////////////////////////////////////
// Alina Sbirlea - alina@rice.edu
// Adapted for CnC-HC after Sagnak Tasirlar's Cholesky for HJ-CnC
// influenced by Aparna Chandramowlishwaran's Intel CnC C++ implementation
// and by Zoran Budimlic's Habanero CnC Java implementation
// 
// Updated for CnC-OCR by Nick Vrvilo (nick.vrvilo@rice.edu)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// graph parameters

$context {
    int numTiles;
    int tileSize;
};

////////////////////////////////////////////////////////////////////////////////
// item collection declarations

[ double *Lkji: j, i, k ];  // The input/intermediate matrix tiles
[ double *results: i ];     // The result matrix tiles

////////////////////////////////////////////////////////////////////////////////
// Input output relationships (comments are Aparna's )

// Root of the prescription tree
( rootComputeStep: () ) -> ( kComputeStep: { 0 .. #numTiles } );

// The kComputeStep produces 'k' loop indices (in the form of tag instance )
( kComputeStep: k ) -> ( kjComputeStep: k ), ( s1ComputeStep: k );

// The kjCompute step produces 'j' loop indices (in the form of tag instance )
( kjComputeStep: k, j )
 -> ( kjiComputeStep: k, { k+1 .. #numTiles } ),
    ( s2ComputeStep:  k, { k+1 .. #numTiles } );

// The kjiComputeStep produces 'i' loop indices (in the form of tag instance )
( kjiComputeStep: k, j ) -> ( s3ComputeStep: k, j, { k+1 .. j+1 } );

// Step 1 Executions
( s1ComputeStep: k )
 <- [ Lkji1D @ Lkji: k, k, k ]
 -> [ Lkji: k, k, k+1 ];
 
// Step 2 Executions
( s2ComputeStep: k, j )
 <- [ LkjiA1D @ Lkji: j, k, k ],
    [ LkjiB1D @ Lkji: k, k, k+1 ]
 -> [ Lkji: j, k, k+1 ];

// Step 3 Executions
( s3ComputeStep: k, j, i )
 <- [ LkjiA1D @ Lkji: j, i, k ],
    [ LkjiB1D @ Lkji: j, k, k+1 ],
    [ LkjiC1D @ Lkji: i, k, k+1 ]
 -> [ Lkji: j, i, k+1 ];

// Input from the caller: tile pointers, tile size and loop end value
( $init: () )
 -> [ startTime: () ],
    ( kComputeStep: () );
 
// Return to the caller
// NOTE: tileCount is the total number of result tiles;
//       numTiles is the number of tiles in the first column of the matrix.
( $finalize: tileCount ) <- [ results: { 0 .. tileCount } ];

// NOTE:
// j = matrix tile's row
// i = matrix tile's column
// k = iteration number (up to i+1)
