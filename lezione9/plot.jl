#%%
#using Pkg
#
#Pkg.add("DataFrames")
#Pkg.add("CSV")
#Pkg.add("Plots")
#%%
# using DataFrames
# using CSV
using Plots
#%%
# run(`./pi2`)
x=-5:0.1:0
f(x)=x^3-3*x^2+x+5
y=f.(x)

plot(x,y)
xaxis!("x")
yaxis!("y")
