# -*- coding: utf-8 -*-
"""
Created on Mon Oct 05 18:54:15 2020

@author: Paula
"""

import numpy as np
import glob
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.animation import FuncAnimation

# Set up formatting for the movie files
Writer = animation.writers['ffmpeg']
writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)

#%%

# PARA RECREAR LA FIG 1 DEL PAPER

N_I_001 =np.loadtxt('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P 0.01\N_I_mean_0.01.txt')

N_I_01 =np.loadtxt('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P 0.10\N_I_mean_0.10.txt')

N_I_1 =np.loadtxt('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P 1.00\N_I_mean_1.00.txt')

N_I_0 =np.loadtxt('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P 0.00\N_I_mean_0.00.txt')

time = np.arange(300)

plt.plot(time,N_I_0*0.1,'b-',label='p = 0')
plt.plot(time,N_I_001*0.1,'r-',label='p = 0.01')
plt.plot(time,N_I_01*0.1,'g-',label='p = 0.1')
plt.plot(time,N_I_1*0.1,'k-',label='p = 1')

plt.xlabel('time',fontsize=13)
plt.ylabel('$N_I$',fontsize=13)
plt.xticks(fontsize=11)
plt.yticks(fontsize=11)
plt.legend(fontsize=11)
plt.grid()
#plt.savefig('Figura1.png')

#%%

# PARA LA VISUALIZACION

Probs = [0.00, 0.01, 0.10, 1.00]
        
prob = 3

all_frames_files_inf = glob.glob('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P '+'{0:.2f}'.format(float(Probs[prob]))+'\INF_P'+'{0:.2f}'.format(float(Probs[prob]))+'_*.txt')
all_frames_files_sus = glob.glob('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P '+'{0:.2f}'.format(float(Probs[prob]))+'\SUS_P'+'{0:.2f}'.format(float(Probs[prob]))+'_*.txt')
all_frames_files_rec = glob.glob('C:\Users\Paula\Documents\Facultad\Fisica Computacional\Final\Codigo\P '+'{0:.2f}'.format(float(Probs[prob]))+'\REC_P'+'{0:.2f}'.format(float(Probs[prob]))+'_*.txt')

all_frames_inf = []
all_frames_sus = []
all_frames_rec = []
for i in range(len(all_frames_files_inf)):
    all_frames_inf.append(np.loadtxt(all_frames_files_inf[i]))
    all_frames_sus.append(np.loadtxt(all_frames_files_sus[i]))
    all_frames_rec.append(np.loadtxt(all_frames_files_rec[i]))

    x_all_inf = []
    y_all_inf = []
    
    x_all_sus = []
    y_all_sus = []
    
    x_all_rec = []
    y_all_rec = []
    for j in range(len(all_frames_inf)):
        x_inf = []
        y_inf = []
        x_sus = []
        y_sus = []
        x_rec = []
        y_rec = []
        i=0
        while i < len(all_frames_inf[j]):
            x_inf.append(all_frames_inf[j][i])
            y_inf.append(all_frames_inf[j][i+1])
            i = i+2
        s=0
        while s < len(all_frames_sus[j]):
            x_sus.append(all_frames_sus[j][s])
            y_sus.append(all_frames_sus[j][s+1])
            s = s+2
        r=0
        while r < len(all_frames_rec[j]):
            x_rec.append(all_frames_rec[j][r])
            y_rec.append(all_frames_rec[j][r+1])
            r = r+2
            
            
        x_all_inf.append(x_inf)
        y_all_inf.append(y_inf)
        x_all_sus.append(x_sus)
        y_all_sus.append(y_sus)
        x_all_rec.append(x_rec)
        y_all_rec.append(y_rec)
    


fig, ax = plt.subplots(figsize=(5, 3))
ax.set(xlim=(-2, 34), ylim=(-2, 34))
    
line_inf = ax.plot(x_all_inf[0], y_all_inf[0], color='r', marker = '*', linewidth = 0)[0]
line_sus = ax.plot(x_all_sus[0], y_all_sus[0], color='y', marker = '.', linewidth = 0)[0]
line_rec = ax.plot(x_all_rec[0], y_all_rec[0], color='b', marker = '.', linewidth = 0)[0]

def animate(i):
    line_inf.set_xdata(x_all_inf[i][:])
    line_inf.set_ydata(y_all_inf[i][:])
    line_sus.set_xdata(x_all_sus[i][:])
    line_sus.set_ydata(y_all_sus[i][:])
    line_rec.set_xdata(x_all_rec[i][:])
    line_rec.set_ydata(y_all_rec[i][:])
    ax.set_title('Frame ' + str(i) + ' / Pj = %.2f' % Probs[prob])
    plt.draw()


anim = FuncAnimation(
    fig, animate, interval=100, frames=len(all_frames_inf))

#plt.show()

anim.save('Animacion_P%.2f.mp4' % Probs[prob], writer=writer)




