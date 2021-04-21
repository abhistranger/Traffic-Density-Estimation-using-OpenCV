#!/usr/bin/env python
# coding: utf-8

# In[3]:


import pandas as pd
import numpy as np
data = pd.read_csv('out.txt',sep=',')
data = pd.DataFrame(data)
data.index+=1
df1=data[:-1]
df2=data[len(data)-1:]
df2=df2.set_index("framenum")


# In[24]:


get_ipython().run_line_magic('matplotlib', 'notebook')
import matplotlib as mpl
import matplotlib.pyplot as plt
fig = plt.figure(figsize=(10,6))
plt.plot(df1["queue density"])
plt.plot(df1["dynamic density"])
plt.ylabel('Density')
plt.xlabel('Time(sec)')
ax=plt.gca()
ax.set_xticklabels([0,0,50,100,150,200,250,300,350,400])
plt.title('Queue and Dynamic density for baseline',fontsize=14)
plt.legend(labels=["queue density","dynamic density"])
plt.axvline(x=490, color="g",linestyle='--')
plt.axvline(x=1400, color="g",linestyle='--')
plt.axvline(x=1060, color="r",linestyle='--')
plt.axvline(x=220, color="r",linestyle='--')
plt.savefig('baseline.png')


# In[ ]:




