#ifndef GLOBAL_H
#define	GLOBAL_H

// Note: with current design width can only be 8
// due to the limitation of bits per port and the limitation of memory
#define WIDTH 8
#define HEIGHT 16

// 16MHz
#define _XTAL_FREQ 16000000

// Size of the shape the current user is holding.
// this is larger than the shape's actual size, but rotation is better if the shape can be centered.
// 6 seems to be working fine.
// While there are two constants, current impl. of rotation will fail if they are not the same
#define CURRENT_BLOCK_WIDTH 6
#define CURRENT_BLOCK_HEIGHT 6

#endif

