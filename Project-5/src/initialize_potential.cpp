
#include <iostream>
#include <armadillo>
#include <cmath>

int main()
{
    // initialize potential to simulate wall 

    size_t Nx=41, Ny = 41;
    double wall_xwidth_01 = 0.05; // along x direction, in 0,1 domain
    double slit_ywidth_01 = 0.05; // along y direction, in 0,1 domain
    double wall_xhwidth_01 = wall_xwidth_01 / 2; // wall half width along x dir
    double slit_yhwidth_h_01 = slit_ywidth_01 / 2; // slit half width along y dir
    int wall_inf = 1000000; //approximate wall to a very large potential

    // to go from 0,1 domain to domain in grid indexes should multiply by tot n grid points
    int NS = 3; //number of slits
    double y0, lowb, upb;



    //
    // initialize the potential to 0 at all points
    //
    arma::mat V_matr = arma::zeros<arma::mat>(Nx, Ny);


    //
    // set the pontial to inf for all y within x range
    //
       // lower and upper bounds for wall along x dir, in grid indexes domain
       double wall_x_low = ceil((0.5 - wall_xhwidth_01) * (Nx-1));
       double wall_x_up = floor((0.5 + wall_xhwidth_01) * (Nx-1));
  
     // loop over grid points inside wall
       for (size_t i = wall_x_low; i <= wall_x_up; i++)
       { 
           for (size_t j = 0; j < Ny; j++)
	     { 
              V_matr(i, j) = wall_inf;
             }
       }



    //
    // working on the lower half grid first since wall is symmetrical along y
    // now set the slits
    //


       // find first grid point to start from; 
       // depending on wheter we have an even or odd number of slits, the midpoint of the cell is wall or slit
       // we start from the midpoint=0.5 and define y0 as the upper position of the first slit
       if (NS % 2 == 0)
	  { 
           y0 = 0.5 - slit_yhwidth_h_01;
          }
       else if (NS % 2 == 1) 
          { 
           y0 = 0.5 + slit_yhwidth_h_01; 
          }
      
       // since we are working on half grid we need to find half the number of slits. rounding with ceil needed in case of odd NS, e.g. NS=3, we need hNS=2; 
       double float2 = 2.0;
       double hNS = ceil(NS / float2);       

       // once y0 is defined, we can find the lower and upperbounds of all slits via a loop, and set the potential to infinite
       for (int ns = 1 ; ns <= hNS ; ns++)
       {
         double k = 2 * ns * slit_ywidth_01 ; //useful to calculate once to reduce FLOPs
	 double l = y0 -k + slit_ywidth_01;

           // defining y0 different for the case of odd and even NS allows us to use the same code for setting the slits
           // (Ny-1) factor is again needed to go from 0,1 domain to grid points
           lowb = ceil( l * (Ny-1));
           upb = floor((l + slit_ywidth_01) * (Ny-1));
           

           for (size_t i = wall_x_low; i <= wall_x_up; i++)
           {
                for (size_t j = lowb; j < upb; j++)
                  {
                     V_matr(i, j) = 0;
                  }
           }

       }  


    //
    // now mirror bottom half grid vertically onto upper half 
    //	
       for (size_t i = wall_x_low; i <= wall_x_up; i++)
       {
           for (size_t j = 0; j < Ny/2; j++)
             {
              V_matr(i, Ny - j - 1) = V_matr(i, j);
             }
       }

std::cout << V_matr ;
}
