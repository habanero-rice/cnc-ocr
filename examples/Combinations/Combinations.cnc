////////////////////////////////////////////////////////////////////////////////
// Author: Nick Vrvilo (nick.vrvilo@rice.edu)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TG Workshop 3 tutorial example for CnC-OCR
// Computing n-choose-k using Pascal's triangle
//
// Takes two non-negative integer arguments: n and k
// Computes the first n rows of Pascal's triangle to find
// the value n-choose-k, and prints the result.
////////////////////////////////////////////////////////////////////////////////

// Graph context stores the parameters "n" and "k"
$context {
  u32 n, k;
};

// Item collection for individual cells of Pascal's triangle
[ u64 cells: row, column ];

// Step collection for generating the all of the cells
// down the left-hand edge of the triangle. No input needed
// since all of the edge entries are just 1.
( addToLeftEdge:     row,   col )
 -> [ cells:         row,   col ],
    ( addToLeftEdge: row+1, col );

// Step collection for generating the all of the cells
// down the right-hand edge of the triangle. No input
// needed since all of the edge entries are just 1.
// Note that this step expands the right-hand edge by
// prescribing two steps instead of just one.
( addToRightEdge:     row,   col   )
 -> [ cells:          row,   col   ],
    ( addToInside:    row+1, col   ),
    ( addToRightEdge: row+1, col+1 );

// Step collection for generating the all of the cells
// on the inside of the triangle. These values are computed
// by summing the two parent cells above (skewed left), which
// are read in as the inputs "a" and "b".
( addToInside:     row,   col   )
 <- [ a @ cells:   row-1, col-1 ],
    [ b @ cells:   row-1, col   ]
 -> [ cells:       row,   col   ],
    ( addToInside: row+1, col   );

// We initialize the graph by putting the top-most value of
// the triangle, then calling the steps to compute the two
// edge cells in the next row. These edge cell entries spawn
// the computation for the rest of the triangle.
( $init: () )
 -> [ cells:          0, 0 ],
    ( addToLeftEdge:  1, 0 ),
    ( addToRightEdge: 1, 1 );

// The computation is done when we've computed [ cells: n, k ].
( $finalize: n, k ) <- [ totalChoices @ cells: n, k ]; 
