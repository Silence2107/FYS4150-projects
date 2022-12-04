

#include "../include/many_slit_initializer.h"
#include <cmath>

double many_slit_potential(double x, double y, double slit_center_x, double slit_center_y, double slit_width_x, double slit_width_y, double slit_spacing, size_t slit_number, double scale)
{
    // must be as efficient as possible, so no loops
    // potential is 0 most of the times

    // easiest to check if x can be within the wall
    if (std::abs(x - slit_center_x) < slit_width_x / 2)
    {
        // now there is a chance that we are in a slit/wall

        double centered_y = y - slit_center_y;

        // consider y > slit_center_y only
        if (centered_y < 0)
            centered_y = -centered_y; // mirror y


        double y_in_slit; // to be explained further
        double depth; // to be explained further

        // if numbers of slits is even, we have a piece of wall in the middle
        if (slit_number % 2 == 0)
        {
            // introduce an offset y variable, which starts from the first slit
            y_in_slit = centered_y - slit_spacing / 2;

            // exclude the central wall piece from consideration
            if (y_in_slit < 0.0)
            {
                return scale;
            }

            // now y covers at least one slit at y > slit_center_y

            // find the slit number we're in
            size_t slit_num = y_in_slit / (slit_width_y + slit_spacing); // integer division, guaranteed to be >=0
            // if we exceed number of slits, we're in the wall
            if (slit_num >= slit_number / 2)
            {
                return scale;
            }
            depth = y_in_slit - slit_num * (slit_width_y + slit_spacing);

        }
        else 
        {
            // slit in the middle
            // introduce an offset y variable, which starts from the second slit
            y_in_slit = centered_y - slit_width_y / 2 - slit_spacing;

            // exclude the central slit from consideration
            if (centered_y < slit_width_y / 2)
            {
                return 0.0;
            }
            // exclude the first wall piece from consideration
            if (centered_y >= slit_width_y / 2 && y_in_slit < 0.0)
            {
                return scale;
            }

            // now y covers at least one slit at y > slit_center_y + slit_spacing

            // find the slit number we're in
            size_t slit_num = y_in_slit / (slit_width_y + slit_spacing); // integer division, guaranteed to be >=0
            // if we exceed number of slits, we're in the wall
            if (slit_num >= (slit_number - 1) / 2)
            {
                return scale;
            }
            depth = y_in_slit - slit_num * (slit_width_y + slit_spacing);
        }

        // depth is organized as follows: [0:slit_width_y] corresponds to the slit, [slit_width_y:slit_width_y+slit_spacing] corresponds to the wall
        if (depth > slit_width_y)
        {
            return scale;
        }
    }
    return 0.0;
}