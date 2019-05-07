using DataFrames
using CSV
using Plots
#%%
# run(`./pi2`)
x=-1:0.1:5
f(x)=exp(-x)-x
y=f.(x)

plot(x,y)
xaxis!("x")
yaxis!("y")

#%%
using Pkg

Pkg.add("ClusterManagers")

#%%
using ClusterManagers
using Distributed

n_processes=5
ENV["HOSTNAME"]="127.0.0.1"
ClusterManagers.addprocs_htc(n_processes)

#%%
@distributed for i=1:n_processes
       run(`hostname`)
       end
