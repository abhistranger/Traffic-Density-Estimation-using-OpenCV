#!/usr/bin/env python
# coding: utf-8

# In[21]:


import pandas as pd
import numpy as np
base = pd.read_csv('out.txt',sep=',')
data1 = pd.read_csv('out_method4_NUM_THREADS_2.txt',sep=',')
data2 = pd.read_csv('out_method4_NUM_THREADS_3.txt',sep=',')
data3 = pd.read_csv('out_method4_NUM_THREADS_4.txt',sep=',')
data4 = pd.read_csv('out_method4_NUM_THREADS_5.txt',sep=',')
base = pd.DataFrame(base)
data1 = pd.DataFrame(data1)
data2 = pd.DataFrame(data2)
data3 = pd.DataFrame(data3)
data4 = pd.DataFrame(data4)
base.index+=1
data1.index+=1
data2.index+=1
data3.index+=1
data4.index+=1
df0=base[:-1]
df1=data1[:-1]
df2=data2[:-1]
df3=data3[:-1]
df4=data4[:-1]
tf0=base[len(base)-1:]
tf1=data1[len(data1)-1:]
tf2=data2[len(data2)-1:]
tf3=data3[len(data3)-1:]
tf4=data4[len(data4)-1:]
df0


# In[22]:


get_ipython().run_line_magic('matplotlib', 'notebook')
import matplotlib as mpl
import matplotlib.pyplot as plt
fig = plt.figure(figsize=(7,6))
width = 0.5
plt.bar("baseline\n(x=1)",tf0["queue density"],width)
plt.bar("x=2",tf1["queue density"],width)
plt.bar("x=3",tf2["queue density"],width)
plt.bar("x=4",tf3["queue density"],width)
plt.bar("x=5",tf4["queue density"],width)
plt.ylabel('Running Time(milisec)')
plt.xlabel('Number of Threads(x)')
plt.title('Method4 Running Time Comparision',fontsize=14)
plt.savefig('method4_1.png')


# In[23]:


fig = plt.figure(figsize=(7,6))
plt.plot(["baseline\n(x=1)","x=2","x=3","x=4","x=5"],[tf0.loc[1913,"queue density"],tf1.loc[1913,"queue density"],tf2.loc[1913,"queue density"],tf3.loc[1913,"queue density"],tf4.loc[1913,"queue density"]],linewidth=2,marker='o')
plt.ylabel('Running Time(milisec)')
plt.xlabel('Number of Threads(x)')
plt.title('Method4 Running Time Comparison',fontsize=14)
plt.savefig('method4_2.png')


# In[24]:


for i in df0.index:
    df1.loc[i,"error_queue"]=(df0.loc[i,"queue density"]-df1.loc[i,"queue density"])**2
    df1.loc[i,"error_dynamic"]=(df0.loc[i,"dynamic density"]-df1.loc[i,"dynamic density"])**2
for i in df0.index:
    df2.loc[i,"error_queue"]=(df0.loc[i,"queue density"]-df2.loc[i,"queue density"])**2
    df2.loc[i,"error_dynamic"]=(df0.loc[i,"dynamic density"]-df2.loc[i,"dynamic density"])**2
for i in df0.index:
    df3.loc[i,"error_queue"]=(df0.loc[i,"queue density"]-df3.loc[i,"queue density"])**2
    df3.loc[i,"error_dynamic"]=(df0.loc[i,"dynamic density"]-df3.loc[i,"dynamic density"])**2
for i in df0.index:
    df4.loc[i,"error_queue"]=(df0.loc[i,"queue density"]-df4.loc[i,"queue density"])**2
    df4.loc[i,"error_dynamic"]=(df0.loc[i,"dynamic density"]-df4.loc[i,"dynamic density"])**2
l_q=[]
l_d=[]
l_q+=[(sum(df1["error_queue"])/len(df0))**0.5,(sum(df2["error_queue"])/len(df0))**0.5,(sum(df3["error_queue"])/len(df0))**0.5,(sum(df4["error_queue"])/len(df0))**0.5]
l_d+=[(sum(df1["error_dynamic"])/len(df0))**0.5,(sum(df2["error_dynamic"])/len(df0))**0.5,(sum(df3["error_dynamic"])/len(df0))**0.5,(sum(df4["error_dynamic"])/len(df0))**0.5]


# In[25]:


fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(10,6))
ax1.set_xticklabels([0,0,100,200,300,400])
ax2.set_xticklabels([0,0,100,200,300,400])
ax3.set_xticklabels([0,0,100,200,300,400])
ax4.set_xticklabels([0,0,100,200,300,400])
fig.suptitle('Relative Error wrt baseline for Queue Density')
ax1.plot(df1["error_queue"])
ax1.set_title('x=2')
ax2.plot(df2["error_queue"], 'tab:orange')
ax2.set_title('x=3')
ax3.plot(df3["error_queue"], 'tab:green')
ax3.set_title('x=4')
ax4.plot(df4["error_queue"], 'tab:red')
ax4.set_title('x=5')
for ax in fig.get_axes():
    ax.set(xlabel='Time(sec)', ylabel='Relative Error')
for ax in fig.get_axes():
    ax.label_outer()
plt.savefig('method4_3.png')


# In[26]:


fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(10,6))
ax1.set_xticklabels([0,0,100,200,300,400])
ax2.set_xticklabels([0,0,100,200,300,400])
ax3.set_xticklabels([0,0,100,200,300,400])
ax4.set_xticklabels([0,0,100,200,300,400])
fig.suptitle('Relative Error wrt baseline for Dynamic Density')
ax1.plot(df1["error_dynamic"])
ax1.set_title('x=2')
ax2.plot(df2["error_dynamic"], 'tab:orange')
ax2.set_title('x=3')
ax3.plot(df3["error_dynamic"], 'tab:green')
ax3.set_title('x=4')
ax4.plot(df4["error_dynamic"], 'tab:red')
ax4.set_title('x=5')
for ax in fig.get_axes():
    ax.set(xlabel='Time(sec)', ylabel='Relative Error')
for ax in fig.get_axes():
    ax.label_outer()
plt.savefig('method4_4.png')


# In[27]:


fig = plt.figure(figsize=(8,7))
plt.plot(['2','3','4','5'],l_q,marker="o")
plt.ylabel('RMS Error')
plt.xlabel('Number of Threads(x)')
plt.title('RMS Error wrt baseline for Queue Density of method 4',fontsize=14)
plt.savefig('method4_5.png')


# In[28]:


fig = plt.figure(figsize=(10,7))
plt.plot(['2','3','4','5'],l_d,marker="o")
plt.ylabel('RMS Error')
plt.xlabel('Number of Threads(x)')
plt.title('RMS Error wrt baseline for Dynamic Density of method 4',fontsize=14)
plt.savefig('method4_6.png')


# In[29]:


l_q_=[]
for i in l_q:
    l_q_+=[1/i,]
l_d_=[]
for j in l_d:
    l_d_+=[1/j,]


# In[30]:


fig = plt.figure(figsize=(9,7))
plt.plot(['2','3','4','5'],l_q_,marker="o")
plt.ylabel('Utility')
plt.xlabel('Number of Threads(x)')
plt.title('Utility for Queue Density of method 4',fontsize=14)
plt.savefig('method4_7.png')


# In[31]:


fig = plt.figure(figsize=(9,7))
plt.plot(['2','3','4','5'],l_d_,marker="o")
plt.ylabel('Utility')
plt.xlabel('Number of Threads(x)')
plt.title('Utility for Dynamic Density of method 4',fontsize=14)
plt.savefig('method4_8.png')


# In[32]:


fig = plt.figure(figsize=(10,7))
plt.plot(df0["dynamic density"])
plt.plot(df1["dynamic density"])
#plt.plot(df2["dynamic density"])
#plt.plot(df3["dynamic density"])
#plt.plot(df4["dynamic density"])
#plt.plot(df5["dynamic density"])
plt.ylabel('Density')
plt.xlabel('Time(sec)')
ax=plt.gca()
ax.set_xticklabels([0,0,50,100,150,200,250,300,350,400])
plt.title('Dynamic density',fontsize=14)


# In[ ]:





# In[ ]:





# In[ ]:




