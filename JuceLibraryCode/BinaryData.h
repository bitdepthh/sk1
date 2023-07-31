/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   logo1_jpg;
    const int            logo1_jpgSize = 239549;

    extern const char*   logo2_jpg;
    const int            logo2_jpgSize = 149222;

    extern const char*   brass_wav;
    const int            brass_wavSize = 3151550;

    extern const char*   brassvib_wav;
    const int            brassvib_wavSize = 3151550;

    extern const char*   drums_wav;
    const int            drums_wavSize = 3151550;

    extern const char*   drumsvib_wav;
    const int            drumsvib_wavSize = 3151550;

    extern const char*   flute_wav;
    const int            flute_wavSize = 3151550;

    extern const char*   flutevib_wav;
    const int            flutevib_wavSize = 3151550;

    extern const char*   human_wav;
    const int            human_wavSize = 3151550;

    extern const char*   humanvib_wav;
    const int            humanvib_wavSize = 3151550;

    extern const char*   jazz_wav;
    const int            jazz_wavSize = 3151550;

    extern const char*   jazzvib_wav;
    const int            jazzvib_wavSize = 3151550;

    extern const char*   piano_wav;
    const int            piano_wavSize = 3151550;

    extern const char*   pianovib_wav;
    const int            pianovib_wavSize = 3151550;

    extern const char*   pipe_wav;
    const int            pipe_wavSize = 3151550;

    extern const char*   pipevib_wav;
    const int            pipevib_wavSize = 3151550;

    extern const char*   trumpet_wav;
    const int            trumpet_wavSize = 3151550;

    extern const char*   trumpetvib_wav;
    const int            trumpetvib_wavSize = 3151550;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 18;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
