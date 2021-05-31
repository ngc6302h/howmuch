#include <AsciiStringView.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double distance(double x1, double y1, double z1, double x2, double y2,
                double z2)
{
    return sqrt((x2 - x1) * (x2 - x1)) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 * z1);
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Invalid argument count\n");
        printf("Usage:\n"
               "howmuch [filament diameter (mm)] [density of filament (g/cm3)] "
               "[gcode file]\n"
               "Example: howmuch 1.75 1.04 print.gcode\n");
        return -1;
    }
    
    FILE* file = fopen(argv[3], "r");
    
    double filament_extruded = 0.;
    double diameter = strtod(argv[1], nullptr);
    double density = strtod(argv[2], nullptr);
    double e = 0.;
    char* buffer = nullptr;
    size_t buffer_size = 0;
    while (!feof(file))
    {
        size_t length = getline(&buffer, &buffer_size, file);
        if (!length || buffer[0] == ';')
            continue;
        
        AsciiStringView view = buffer;
        
        if (view.starts_with("G92 E0"))
        {
            e = 0.;
            continue;
        }
        
        if (!view.starts_with("G0") && !view.starts_with("G1"))
            continue;
        
        double new_e = 0.;
        auto coord_pos = view.contains("E");
        if (coord_pos != view.cend())
        {
            new_e = strtod(coord_pos->data + 1, nullptr);
        }
        
        if (new_e > 0.)
            filament_extruded += new_e - e;
        
        e = new_e != 0. ? new_e : e;
    }
    fclose(file);
    free(buffer);
    
    printf("Extruded %f mm of filament\n", filament_extruded);
    printf("Estimated weight: %f g.\n",
           filament_extruded * (M_PI * ((diameter / 2.) * (diameter / 2.))) * (density / 1000.));
    return 0;
}
