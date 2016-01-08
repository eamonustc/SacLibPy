#!/home/eamon/anaconda/bin/python
import obspy.core
import numpy as np
import matplotlib.pyplot as plt
import saclibpy

# filtreing parameters
delta = 0.02
freq_min = 0.01
freq_max = 0.7
order = 4
passes = 1

# load data
tr_data = obspy.core.read("./data/data_test.sac")
data = tr_data[0].data
time = np.arange(0, tr_data[0].stats.npts*tr_data[0].stats.delta, tr_data[0].stats.delta)

# filtering data
filt_data = data.copy()
saclibpy.sacxapiir(filt_data, 0.0, 0.0, order, freq_min, freq_max, delta, passes)

fig = plt.figure()
ax1 = fig.add_subplot(211)
plt.plot(time, data, 'k-')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude (m/s)")

ax2 = fig.add_subplot(212)
plt.plot(time, filt_data, 'r-')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude (m/s)")
plt.show()
