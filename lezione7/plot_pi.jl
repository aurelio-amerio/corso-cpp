using DataFrames
using CSV
using Plots
#%%
run(`./pi2`)
file1 = open("error_empirical.dat")
file2 = open("error_theo.dat")
df1=CSV.read(file1, header=false, delim=" ")
df2=CSV.read(file2, header=false, delim=" ")

plot(df1[1],df1[2], label="empirical", title="Monte Carlo Pi error")
plot!(df2[1],df2[2], label="theoretical")
xaxis!("N", xscale= :log10)
yaxis!("error", ylims=(1e-3,10), yscale= :log10)
