#!/usr/bin/env python
# coding: utf-8

# In[14]:


import pandas as pd
import numpy as np
base = pd.read_csv('out.txt',sep=',')
data1 = pd.read_csv('out_method2_XxY_250x750.txt',sep=',')
data2 = pd.read_csv('out_method2_XxY_200x600.txt',sep=',')
data3 = pd.read_csv('out_method2_XxY_150x450.txt',sep=',')
data4 = pd.read_csv('out_method2_XxY_100x300.txt',sep=',')
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


# In[15]:


get_ipython().run_line_magic('matplotlib', 'notebook')
import matplotlib as mpl
import matplotlib.pyplot as plt
fig = plt.figure(figsize=(7,6))
width = 0.5
plt.bar("baseline\n(approx=290x900)",tf0["queue density"],width)
plt.bar("XxY=250x750",tf1["queue density"],width)
plt.bar("XxY=200x600",tf2["queue density"],width)
plt.bar("XxY=150x450",tf3["queue density"],width)
plt.bar("XxY=100x300",tf4["queue density"],width)
plt.ylabel('Running Time(milisec)')
plt.xlabel('Parameter Resolution')
plt.title('Method2 Running Time Comparision',fontsize=14)
plt.savefig('method2_1.png')


# In[16]:


fig = plt.figure(figsize=(7,6))
width = 0.5
plt.plot(["baseline\n(approx=290x900)","XxY=250x750","XxY=200x600","XxY=150x450","XxY=100x300"],[tf0.loc[1913,"queue density"],tf1.loc[1913,"queue density"],tf2.loc[1913,"queue density"],tf3.loc[1913,"queue density"],tf4.loc[1913,"queue density"]],linewidth=2,marker='o')
plt.ylabel('Running Time(milisec)')
plt.xlabel('Parameter Resolution')
plt.title('Method2 Running Time Comparison',fontsize=14)
plt.savefig('method2_2.png')


# In[17]:


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


# In[18]:


l_q,l_d


# In[19]:


fig = plt.figure(figsize=(10,7))
plt.plot(df1["error_queue"]*100)
plt.ylabel('Relative Error Percentage')
plt.xlabel('Time(sec)')
ax=plt.gca()
ax.set_xticklabels([0,0,50,100,150,200,250,300,350,400])
plt.title('Relative Error Percentage wrt baseline for XxY = 250x750',fontsize=14)
#plt.legend(labels=["dense dynamic density","sparse dynamic density"])
#plt.savefig('method_extra_1.png')
df1


# In[20]:


fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(10,6))
ax1.set_xticklabels([0,0,100,200,300,400])
ax2.set_xticklabels([0,0,100,200,300,400])
ax3.set_xticklabels([0,0,100,200,300,400])
ax4.set_xticklabels([0,0,100,200,300,400])
fig.suptitle('Relative Error wrt baseline for Queue Density')
ax1.plot(df1["error_queue"])
ax1.set_title('XxY=250x750')
ax2.plot(df2["error_queue"], 'tab:orange')
ax2.set_title('XxY=200x600')
ax3.plot(df3["error_queue"], 'tab:green')
ax3.set_title('XxY=150x450')
ax4.plot(df4["error_queue"], 'tab:red')
ax4.set_title('XxY=100x300')
for ax in fig.get_axes():
    ax.set(xlabel='Time(sec)', ylabel='Relative Error')
for ax in fig.get_axes():
    ax.label_outer()
plt.savefig('method2_3.png')


# In[21]:


fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(10,6))
ax1.set_xticklabels([0,0,100,200,300,400])
ax2.set_xticklabels([0,0,100,200,300,400])
ax3.set_xticklabels([0,0,100,200,300,400])
ax4.set_xticklabels([0,0,100,200,300,400])
fig.suptitle('Relative Error wrt baseline for Dynamic Density')
ax1.plot(df1["error_dynamic"])
ax1.set_title('XxY=250x750')
ax2.plot(df2["error_dynamic"], 'tab:orange')
ax2.set_title('XxY=200x600')
ax3.plot(df3["error_dynamic"], 'tab:green')
ax3.set_title('XxY=150x450')
ax4.plot(df4["error_dynamic"], 'tab:red')
ax4.set_title('XxY=100x300')
for ax in fig.get_axes():
    ax.set(xlabel='Time(sec)', ylabel='Relative Error')
for ax in fig.get_axes():
    ax.label_outer()
plt.savefig('method2_4.png')


# In[22]:


fig = plt.figure(figsize=(10,7))
plt.plot([tf1.loc[1913,"queue density"],tf2.loc[1913,"queue density"],tf3.loc[1913,"queue density"],tf4.loc[1913,"queue density"]],l_q,marker='o')
plt.ylabel('Utility')
plt.xlabel('Runtime(milisec)')


# In[23]:


fig = plt.figure(figsize=(10,7))
plt.plot(['XxY=250x750','XxY=200x600','XxY=150x450','XxY=100x300'],l_q,marker="o")
plt.ylabel('RMS Error')
plt.xlabel('Parameter Resolution: XxY')
plt.title('RMS Error wrt baseline for Queue Density of method 2',fontsize=14)
plt.savefig('method2_5.png')


# In[24]:


fig = plt.figure(figsize=(10,7))
plt.plot(['XxY=250x750','XxY=200x600','XxY=150x450','XxY=100x300'],l_d,marker="o")
plt.ylabel('RMS Error')
plt.xlabel('Parameter Resolution: XxY')
plt.title('RMS Error wrt baseline for Dynamic Density of method 2',fontsize=14)
plt.savefig('method2_6.png')


# In[25]:


l_q_=[]
for i in l_q:
    l_q_+=[1/i,]
l_d_=[]
for j in l_d:
    l_d_+=[1/j,]


# In[26]:


fig = plt.figure(figsize=(10,7))
plt.plot(['XxY=250x750','XxY=200x600','XxY=150x450','XxY=100x300'],l_q_,marker="o")
plt.ylabel('Utility')
plt.xlabel('Parameter Resolution: XxY')
plt.title('Utility for Queue Density of method 2',fontsize=14)
plt.savefig('method2_7.png')


# In[27]:


fig = plt.figure(figsize=(10,7))
plt.plot(['XxY=250x750','XxY=200x600','XxY=150x450','XxY=100x300'],l_d_,marker="o")
plt.ylabel('Utility')
plt.xlabel('Parameter Resolution: XxY')
plt.title('Utility for Dynamic Density of method 2',fontsize=14)
plt.savefig('method2_8.png')


# In[ ]:





# In[ ]:




