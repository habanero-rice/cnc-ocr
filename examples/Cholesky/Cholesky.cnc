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

// The kPrescriptions produces 'k' loop indices (in the form of tag instance )
( kPrescriptions: () )
 -> ( kjPrescriptions: $RANGE(0, #numTiles) ),
    ( serialCholesky: $RANGE(0, #numTiles) );

// The kjCompute step produces 'j' loop indices (in the form of tag instance )
( kjPrescriptions: k )
 -> ( kjiPrescriptions: k, $RANGE(k+1, #numTiles) ),
    ( trisolve:  k, $RANGE(k+1, #numTiles) );

// The kjiPrescriptions produces 'i' loop indices (in the form of tag instance )
( kjiPrescriptions: k, j ) -> ( update: k, j, $RANGE(k+1, j+1) );

// Step 1 Executions
( serialCholesky: k )
 <- [ Lkji1D @ Lkji: k, k, k ]
 -> [ Lkji: k, k, k+1 ];
 
// Step 2 Executions
( trisolve: k, j )
 <- [ LkjiA1D @ Lkji: j, k, k ],
    [ LkjiB1D @ Lkji: k, k, k+1 ]
 -> [ Lkji: j, k, k+1 ];

// Step 3 Executions
( update: k, j, i )
 <- [ LkjiA1D @ Lkji: j, i, k ],
    [ LkjiB1D @ Lkji: j, k, k+1 ],
    [ LkjiC1D @ Lkji: i, k, k+1 ]
 -> [ Lkji: j, i, k+1 ];

// Input from the caller: tile pointers, tile size and loop end value
( $init: () )
 -> [ startTime: () ],
    ( kPrescriptions: () );
 
// Return to the caller
// NOTE: tileCount is the total number of result tiles;
//       numTiles is the number of tiles in the first column of the matrix.
( $finalize: tileCount ) <- [ results: $RANGE(0, tileCount) ];

// NOTE:
// j = matrix tile's row
// i = matrix tile's column
// k = iteration number (up to i+1)
