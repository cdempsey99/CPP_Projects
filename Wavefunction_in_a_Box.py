import matplotlib.pyplot as plt
import numpy as np
import cmath

j = cmath.sqrt(-1)

Nt=2000 # number of time steps

# delta x and delta t
dx=0.1
dt=1e-3
s=dt/dx**2

#Box width and number of space points for a given dx
L=40
N=int(L/dx)

# define x -axis - ghost points not included!
x=np.arange(N)*dx 

#wave packet parameters
sigma=1
k=2
xc=L/2

# define complex wave function – note that we need two additional  
# space points to impose periodic boundary conditions 
phi = np.zeros([Nt,N+2])+0j

A= sigma**(-0.5)*np.pi**(-0.25) # normalisation constant  

# phi is defined between j=1 and j=N; phi[0,0] and phi[0,N+1] are the ghost 
# points at n=0
phi[0,1:(N+1)]=A*np.exp(-(x-xc)**2/(2*sigma**2))*np.exp(1j*k*x)

# update ghost points to impose periodic boundary conditions at n=0, for every time step
phi[0, 0] = phi[0, N]
phi[0, N+1] = phi[0, 1]  #periodic BC

#now use the explicit difference scheme
for i in np.arange(1,N+1):
    phi[1, i] = phi[0, i] + 1j * s * (phi[0, i+1] - 2*phi[0, i] + phi[0, i-1])

phi[1,0] = phi[1, N]
phi[1, N+1] = phi[1, 1]  #reapply periodic BC

for n in range(2, Nt):  #loop over points in time
    for i in np.arange(1,N+1):  #loop over points in space
        phi[n, i] = phi[n-2, i] + 2j * s * (phi[n-1, i+1] - 2 * phi[n-1, i] + phi[n-1, i-1])

    phi[n, 0] = phi[n, N]
    phi[n, N+1] = phi[n, 1] #reapply periodic BC (every iteration)

#the probability density:
prob_density = np.zeros((Nt,N+2))
for n in range(0, Nt):
    for i in np.arange(1, N+1):
        prob_density[n, i] = np.linalg.norm(phi[n, i])**2

#find the integrated prob. density, using the trapeziodal rule:
prob = np.zeros(Nt)
for n in range(0, Nt):
    for i in np.arange(1, N+1):
        prob[n] += dx * prob_density[n, i]

#plot the wavepacket at t=0
fig = plt.figure()
plt.plot(x, prob_density[0, 2:(N+2)])
# at t=1
plt.plot(x, prob_density[1000, 2:(N+2)])
#and t=2
plt.plot(x, prob_density[1999, 2:(N+2)])
plt.xlabel('x')
plt.ylabel('Probability density of Wavefunction')

#plot integrated probability density:
n_list = np.linspace(0, 2, Nt)
plt.scatter(n_list, prob, marker='.')
plt.xlabel('t')
plt.ylabel('Probability')
plt.show()