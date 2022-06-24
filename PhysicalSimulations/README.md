# Physical Simulations
## Numerical Integration
This code aims to use numerical integration (specifically the fourth-order Runge Kutta scheme) and the shooting method to find the solution to a second order differential equation. This demonstrates the power of approximation methods, given that the differential equation in question has no analytic solution.

## N-Body Problem
Here we attempt to use numerical methods to predict the motion of a system of n-bodies in a 2D vacuum, all of which obey Newton's Law of Universal Gravitation (G is taken as unity). The 3D analogue of this is yet another famously impossible problem from an analytic point of view.
 
The algorithm used here is known as the Leap-frog scheme and it is very useful in dealing with systems of classical mechanics. This is because it is time-reversible and hence conserves the energy of the physical system it describes. Here we take n=4, with varying masses. A variety of initial positions and velocities have also been chosen. The positions of each body can be found accurate to 3 significant figures. 

## Laplace Equation
This is a look at partial differential equations, dealing with the very famous second-order PDE, the Laplace Equation. This equation can be seen in everything from electrostatics to the spreading out of heat over time. 

We will attempt to find the values of a field Ф on a 2D grid, given that we know (i) that the field obeys the Laplace equation and (ii) the boundary conditions. In this example we consider Dirichlet boundary conditions (the field becomes zero at the grid edges). We essentially turn the problem of a differential equation into one of linear algebra and apply the Successive Over-Relaxed (SOR) Method.

## Potts Model
The q-state Potts Model is characterised by an LxL grid of points, each with some integer spin associated with them. These integers can be less than or equal to q (Hence the Ising model is the special case of q=2). This model is a very useful approximation of the thermodynamics of magnetic spins of a 2D crystal lattice. 

The fractional magnetisation is defined as (insert picture of equation)

where f(σ) is the fraction of sites containing the most commonly occuring spin in the configuration. In this script we use a Markov Chain method based on the Metropolis algorithm to generate importance-sampling Monte Carlo random configurations of the Potts spin field on a 20 × 20 grid. For a given value of inverse temperature β and q, we can produce a graph which allows us to estimate the average magnetisation <M>.(insert graph)

 ## Wavefunction in a Box
 
 This was a college assignment in which we aimed to model the behaviour of a 1-dimensional quantum mechanical wavefunction in a box of length L, with periodic boundary conditions. The motion of the wavefunction is governed by the Schrodinger equation and the python package cmath is used to produce the necessary complex numbers. We see from the plots of the probability density of the wavefunction, that it not only moves in the positive x-direction with a certain velocity, but also spreads out over time. 
