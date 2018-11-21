
//{{BLOCK(b0)

//======================================================================
//
//	b0, 256x160@4, 
//	+ palette 256 entries, not compressed
//	+ 421 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 512 + 13472 + 1280 = 15264
//
//	Time-stamp: 2018-11-16, 11:47:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_B0_H
#define GRIT_B0_H

#define b0TilesLen 13472
extern const unsigned int b0Tiles[3368];

#define b0MapLen 1280
extern const unsigned short b0Map[640];

#define b0PalLen 512
extern const unsigned short b0Pal[256];

#endif // GRIT_B0_H

//}}BLOCK(b0)
