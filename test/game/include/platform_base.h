
//{{BLOCK(platform_base)

//======================================================================
//
//	platform_base, 32x64@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles Metatiled by 4x8 not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2018-10-27, 11:00:15
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PLATFORM_BASE_H
#define GRIT_PLATFORM_BASE_H

#define platform_baseTilesLen 1024
extern const unsigned int platform_baseTiles[256];

#define platform_basePalLen 32
extern const unsigned short platform_basePal[16];

#endif // GRIT_PLATFORM_BASE_H

//}}BLOCK(platform_base)
