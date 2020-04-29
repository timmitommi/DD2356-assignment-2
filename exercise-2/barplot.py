import matplotlib.pyplot as plt

scheduling = ("static", "dynamic", "guided")
results_scheduling = (47917.8, 365.5, 40856.8)

fig = plt.figure()
ax = fig.add_axes([0,2,1,1])
ax.bar(scheduling,results_scheduling)

plt.show()
