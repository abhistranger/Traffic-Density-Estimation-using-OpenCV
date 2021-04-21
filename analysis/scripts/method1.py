#!/usr/bin/env python
# coding: utf-8

# In[36]:


import pandas as pd
import numpy as np
base = pd.read_csv('out.txt',sep=',')
data1 = pd.read_csv('out_method1_x_2.txt',sep=',')
data2 = pd.read_csv('out_method1_x_4.txt',sep=',')
data3 = pd.read_csv('out_method1_x_6.txt',sep=',')
data4 = pd.read_csv('out_method1_x_8.txt',sep=',')
data5 = pd.read_csv('out_method1_x_10.txt',sep=',')
base = pd.DataFrame(base)
data1 = pd.DataFrame(data1)
data2 = pd.DataFrame(data2)
data3 = pd.DataFrame(data3)
data4 = pd.DataFrame(data4)
data5 = pd.DataFrame(data5)
base.index+=1
data1.index+=1
data2.index+=1
data3.index+=1
data4.index+=1
data5.index+=1
df0=base[:-1]
df1=data1[:-1]
df2=data2[:-1]
df3=data3[:-1]
df4=data4[:-1]
df5=data5[:-1]
tf0=base[len(base)-1:]
tf1=data1[len(data1)-1:]
tf2=data2[len(data2)-1:]
tf3=data3[len(data3)-1:]
tf4=data4[len(data4)-1:]
tf5=data5[len(data5)-1:]


# In[37]:


get_ipython().run_line_magic('matplotlib', 'notebook')
import matplotlib as mpl
import matplotlib.pyplot as plt
fig = plt.figure(figsize=(7,6))
width = 0.5
plt.bar("baseline",tf0["queue density"],width)
plt.bar("x=2",tf1["queue density"],width)
plt.bar("x=4",tf2["queue density"],width)
plt.bar("x=6",tf3["queue density"],width)
plt.bar("x=8",tf4["queue density"],width)
plt.bar("x=10",tf5["queue density"],width)
plt.ylabel('Running Time(milisec)')
plt.title('Method1 Running Time Comparision',fontsize=14)


# In[38]:


fig = plt.figure(figsize=(7,6))
plt.plot(["baseline","x=2","x=4","x=6","x=8","x=10"],[tf0.loc[len(base),"queue density"],tf1.loc[len(data1),"queue density"],tf2.loc[len(data2),"queue density"],tf3.loc[len(data3),"queue density"],tf4.loc[len(data4),"queue density"],tf5.loc[len(data5),"queue density"]],linewidth=2,marker='o')
plt.ylabel('Run Time(milisec)')
plt.xlabel('Parameter x: No of frame to drop')
plt.title('Method1 Run Time Comparison',fontsize=14)
plt.savefig('method1_2.png')


# In[39]:


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
for i in df0.index:
    df5.loc[i,"error_queue"]=(df0.loc[i,"queue density"]-df5.loc[i,"queue density"])**2
    df5.loc[i,"error_dynamic"]=(df0.loc[i,"dynamic density"]-df5.loc[i,"dynamic density"])**2
l_q=[]
l_d=[]
l_q+=[(sum(df1["error_queue"])/len(df0))**0.5,(sum(df2["error_queue"])/len(df0))**0.5,(sum(df3["error_queue"][:-2])/len(df0))**0.5,(sum(df4["error_queue"])/len(df0))**0.5,(sum(df5["error_queue"][:-8])/len(df0))**0.5]
l_d+=[(sum(df1["error_dynamic"])/len(df0))**0.5,(sum(df2["error_dynamic"])/len(df0))**0.5,(sum(df3["error_dynamic"][:-2])/len(df0))**0.5,(sum(df4["error_dynamic"])/len(df0))**0.5,(sum(df5["error_dynamic"][:-8])/len(df0))**0.5]


# In[40]:


l_d,l_q


# In[41]:


fig = plt.figure(figsize=(10,7))
plt.plot(['2','4','6','8','10'],l_q,marker="o")
plt.ylabel('RMS Error')
plt.xlabel('Parameter x: No of frame to drop')
plt.title('RMS Error wrt baseline for Queue Density of method 1',fontsize=14)
plt.savefig('method1_5.png')


# In[42]:


fig = plt.figure(figsize=(10,7))
plt.plot(['2','4','6','8','10'],l_d,marker="o")
plt.ylabel('RMS Error')
plt.xlabel('Parameter x: No of frame to drop')
plt.title('RMS Error wrt baseline for Dynamic Density of method 1',fontsize=14)
plt.savefig('method1_6.png')


# In[43]:


fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(10,6))
ax1.set_xticklabels([0,0,100,200,300,400])
ax2.set_xticklabels([0,0,100,200,300,400])
ax3.set_xticklabels([0,0,100,200,300,400])
ax4.set_xticklabels([0,0,100,200,300,400])
fig.suptitle('Relative Error wrt baseline for Queue Density')
ax1.plot(df1["error_queue"])
ax1.set_title('x=2')
ax2.plot(df2["error_queue"], 'tab:orange')
ax2.set_title('x=4')
ax3.plot(df3["error_queue"], 'tab:green')
ax3.set_title('x=6')
ax4.plot(df4["error_queue"], 'tab:red')
ax4.set_title('x=8')
for ax in fig.get_axes():
    ax.set(xlabel='Time(sec)', ylabel='Relative Error')
for ax in fig.get_axes():
    ax.label_outer()
plt.savefig('method1_3.png')


# In[44]:


fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(10,6))
ax1.set_xticklabels([0,0,100,200,300,400])
ax2.set_xticklabels([0,0,100,200,300,400])
ax3.set_xticklabels([0,0,100,200,300,400])
ax4.set_xticklabels([0,0,100,200,300,400])
fig.suptitle('Relative Error wrt baseline for Queue Density')
ax1.plot(df1["error_dynamic"])
ax1.set_title('x=2')
ax2.plot(df2["error_dynamic"], 'tab:orange')
ax2.set_title('x=4')
ax3.plot(df3["error_dynamic"], 'tab:green')
ax3.set_title('x=6')
ax4.plot(df4["error_dynamic"], 'tab:red')
ax4.set_title('x=8')
for ax in fig.get_axes():
    ax.set(xlabel='Time(sec)', ylabel='Relative Error')
for ax in fig.get_axes():
    ax.label_outer()
plt.savefig('method1_4.png')


# In[45]:


l_q_=[]
for i in l_q:
    l_q_+=[1/i,]
l_d_=[]
for j in l_d:
    l_d_+=[1/j,]


# In[46]:


fig = plt.figure(figsize=(10,7))
plt.plot(['2','4','6','8','10'],l_q_,marker="o")
plt.ylabel('Utility')
plt.xlabel('Parameter x: No of frame to drop')
plt.title('Utility for Queue Density of method 1',fontsize=14)
plt.savefig('method1_7.png')


# In[47]:


fig = plt.figure(figsize=(10,7))
plt.plot(['2','4','6','8','10'],l_d_,marker="o")
plt.ylabel('Utility')
plt.xlabel('Parameter x: No of frame to drop')
plt.title('Utility for Dynamic Density of method 1',fontsize=14)
plt.savefig('method1_8.png')


# In[ ]:





# In[ ]:





# In[ ]:




