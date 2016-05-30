////////////////////////////////////////////////////////////////////////////////
// Author: Nick Vrvilo (nick.vrvilo@rice.edu)
////////////////////////////////////////////////////////////////////////////////

/* Really simple CnC example:
 * The init function prescribes an "SX" and an "SY" step instance.
 * Each step puts a single integer item to the corresponding item collection.
 * (The value of the integer put matches the step's tag value.)
 * The finalize function reads two two items and prints their values.
 */

[ int X: x ];
[ int Y: y ];

( $init: () ) -> ( SX: 1 ), ( SY: 2 );

( SX: x ) -> [ X: 0 ];
( SY: y ) -> [ Y: 0 ];

( $finalize: () ) <- [ X: 0 ], [ Y: 0 ];

/* Original version using singletons
[ int X: () ];
[ int Y: () ];

( $init: () ) -> ( SX: 1 ), ( SY: 2 );

( SX: x ) -> [ X: () ];
( SY: y ) -> [ Y: () ];

( $finalize: () ) <- [ X: () ], [ Y: () ];
*/
