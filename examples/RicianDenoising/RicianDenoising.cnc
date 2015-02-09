$context {
    int numTileRows;
    int numTileCols;
    int blockSize;
    int iters;
    double sigma;  // unused?
    double sigma2;
    double lambda; // unused?
    double gamma;
    int dt;        // unused?
};

// 1. tag collections
//< int [3] iterations >;

// 2. item collections
//[ double parameters ];
[ void *imageData: i, j ];
[ void *uDiffData: iter, pos, i, j ];
[ void *gData: iter, i, j ];
[ void *rData: iter, i, j ];
[ void *ugData: iter, i, j ];
[ void *uData: iter, i, j ];
// added for distributed finish
// (only needed because we don't actually read the output...)
[ int doneFlag: n ];

// 3. step prescriptions
//<iterations> :: (uDiffCompute);
//<iterations> :: (gCompute);
//<iterations> :: (rCompute);
//<iterations> :: (ugCompute);
//<iterations> :: (uCompute);

// 5. Step dependences

// [parameters: TAG_BLOCK_SIZE],
// [parameters: TAG_NUM_TILE_ROWS],
// [parameters: TAG_NUM_TILE_COLS],
 (uDiffCompute : iter, i, j)
<-
 [ U_cen @ uData: iter - 1, i, j ],
 [ U_top @ uData: iter - 1, i - 1, j ] $when (i > 1),
 [ U_lef @ uData: iter - 1, i, j - 1 ] $when (j > 1),
 [ U_bot @ uData: iter - 1, i + 1, j ] $when (i < #numTileRows),
 [ U_rig @ uData: iter - 1, i, j + 1 ] $when (j < #numTileCols)
->
 [uDiffData : iter, TAG_TOP, i, j],
 [uDiffData : iter, TAG_RIG, i, j],
 [uDiffData : iter, TAG_BOT, i, j],
 [uDiffData : iter, TAG_LEF, i, j]
;

// [parameters : TAG_BLOCK_SIZE],
// [parameters : TAG_SIGMA_2],
 (rCompute : iter, i, j)
<-
 [ imgData @ imageData : i, j],
 [ U_last @ uData : iter - 1, i, j ]
->
 [rData : iter, i, j];

// [parameters : TAG_BLOCK_SIZE],
 (gCompute : iter, i, j)
<-
 [ U_last @ uData : iter - 1, i, j ],
 [ U_top @ uDiffData : iter, TAG_TOP, i, j],
 [ U_rig @ uDiffData : iter, TAG_RIG, i, j],
 [ U_bot @ uDiffData : iter, TAG_BOT, i, j],
 [ U_lef @ uDiffData : iter, TAG_LEF, i, j]
->
 [gData : iter, i, j]
;

// [parameters : TAG_BLOCK_SIZE],
// [parameters : TAG_SIGMA_2],
 (ugCompute : iter, i, j)
<-
 [ gData : iter, i, j ],
 [ U_last @ uData : iter - 1, i, j ]
->
 [ ugData : iter, i, j ]
;

// [parameters : TAG_BLOCK_SIZE],
// [parameters : TAG_NUM_TILE_ROWS],
// [parameters : TAG_NUM_TILE_COLS],
// [parameters : TAG_GAMMA],
 (uCompute : iter, i, j)
<-
 [ img_ij @ imageData : i, j ],
 [ ug_cur @ ugData : iter, i, j ],
 [ ug_top @ ugData : iter, i - 1, j ] $when (i > 1),
 [ ug_lef @ ugData : iter, i, j - 1 ] $when (j > 1),
 [ ug_dow @ ugData : iter, i + 1, j ] $when (i < #numTileRows),
 [ ug_rig @ ugData : iter, i, j + 1 ] $when (j < #numTileCols),
 [ gc @ gData : iter, i, j ] $when (i == 1 || j == 1 || i == #numTileRows || j == #numTileCols),
 [ gt @ gData : iter, i - 1, j ] $when (i > 1),
 [ gl @ gData : iter, i, j - 1 ] $when (j > 1),
 [ gd @ gData : iter, i + 1, j ] $when (i < #numTileRows),
 [ gr @ gData : iter, i, j + 1 ] $when (j < #numTileCols),
 [ r_ij @ rData : iter, i, j ],
 [ u_ij @ uData : iter - 1, i,  j]
->
 [uData : iter, i, j],
 [ doneFlag: (i-1)*#numTileCols+(j-1) ]
;

// 4. Environment dependencies
( $init: () )
->
//<iterations>,
//[parameters],
[ imageData: $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) ],
[ uData:  0, $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) ],
(uDiffCompute: $RANGE(1, #iters+1), $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) ),
(gCompute: $RANGE(1, #iters+1), $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) ),
(rCompute: $RANGE(1, #iters+1), $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) ),
(ugCompute: $RANGE(1, #iters+1), $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) ),
(uCompute: $RANGE(1, #iters+1), $RANGE(1, #numTileRows+1), $RANGE(1, #numTileCols+1) )
;

( $finalize: () )
<-
//[parameters],
//[ uData: iter, i, j ]
[ doneFlag: $RANGE(0, #numTileRows*#numTileCols) ]
;

