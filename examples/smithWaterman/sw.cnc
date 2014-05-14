// @author: Alina Sbirlea
// alina@rice.edu

[ int* A ];
//[ struct sw *sw_specific]; //all the common stuff for smith-waterman
[ struct timeval *startTime ]; // Only used for timing the computation

< int [2] cornerTag >;
< int [2] top_borderTag >;
< int [2] left_borderTag >;
< int [2] fulltileTag >;

< cornerTag > :: ( corner );
< top_borderTag > :: ( top_border );
< left_borderTag > :: ( left_border );
< fulltileTag > :: ( fulltile );

( corner : i, j ) -> [ A : i, j ];
[ A : i, j-1 ] -> ( top_border : i, j ) -> [ A : i, j ];
[ A : i-1, j ] -> ( left_border : i, j ) -> [ A : i, j ];
[ A : i-1, j ], [ A : i, j-1 ], [ A : i-1, j-1 ] -> ( fulltile : i, j ) -> [ A : i, j ]; 

( env: NH, NW ) -> [ startTime : 0 ];
( env: NH, NW ) -> < cornerTag : 0, 0 >, < top_borderTag : 0, {1 .. NW+1} >, < left_borderTag : {1 .. NH+1}, 0 >;
( env: NH, NW ) -> < fulltileTag : {1 .. NH+1}, {1 .. NW+1} >;
[ startTime: 0],  [ A : NH, NW ] -> ( env: NH, NW );


