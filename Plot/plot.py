
import numpy as np

# Loadtxt to create an array
data = np.loadtxt('masses.txt' , skiprows=3)

# Counting the events, the M min and the M max
print(f"Numero di eventi: {len(data)}")
print(f"Massa minima: {data.min():.2f} GeV, Massa massima: {data.max():.2f} GeV")

# Defining the histogram and the bins
bin_width = 4.0
m_min = 110
m_max = 160
n_bins = int((m_max - m_min)/bin_width) # Number of bins

# Histogram
counts, bin_edges = np.histogram(data, bins=n_bins, range=(m_min, m_max))
bin_centers = []
for i in range(len(bin_edges) - 1):
    centro = (bin_edges[i] + bin_edges[i+1])/2
    bin_centers.append(centro)

# Converting into the array
bin_centers = np.array(bin_centers)


# Signal + background
def fitfunction(x, A, mu, sigma, a, b):
    gaussian = A * np.exp(-(x-mu)**2)/(2*sigma**2) # Gaussian for the peak
    background = a * x + b # Linear function for the background

    return gaussian + background

# Only background
def background_function(x, a, b):
    return a*x + b

    
from scipy.optimize import curve_fit

# Initial parameters par
# A = 3 (3 events)
# sigma = 2 GeV (detector resolution)
# mu = 125 GeV 
# a = -0.01 (negative slope)
# b = 8

par = [3, 125, 2, -0.01, 2] # ATTENTION: respect the order of the fitfunction (line 29)

# Bounds (A, mu, sigma, a, b)
lower_bounds = [0.1, 120, 0.5, -1, 0]
upper_bounds = [10, 130, 5, 0, 10]

# Fitting
popt, pcov = curve_fit(fitfunction, bin_centers, counts, p0=par, bounds = (lower_bounds, upper_bounds)) # Parameters optimal
perr = np.sqrt(np.diag(pcov)) # Covariance matrix

print(f"Reconstructed Higgs mass: {popt[1]:.2f} +/- {perr[1]:.2f} GeV")
print(f"Peak width: {popt[2]:.2f} +/- {perr[2]:.2f} GeV")


import matplotlib.pyplot as plt

plt.figure(figsize=(9, 6))

plt.errorbar(bin_centers, counts, yerr=np.sqrt(counts), fmt='o', label='Data') 

x_plot = np.linspace(110, 160, 200)

plt.plot(x_plot, fitfunction(x_plot, *popt), color='red', linewidth='2', label='Signal + Bkg fit')
plt.plot(x_plot, popt[3]*x_plot + popt[4], color='blue', linestyle='--', label='Background')

plt.ylabel('Events')
plt.xlabel('Higgs mass')
plt.grid(True)
plt.legend()

plt.savefig('Higgs_plot.png')
plt.show()


