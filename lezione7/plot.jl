using DataFrames
using CSV
using Plots
#%%
file1 = open("rand_decay.dat")
file2 = open("exp_decay.dat")
df1=CSV.read(file1, header=false, delim=" ")
df2=CSV.read(file2, header=false, delim=" ")
#%%
plot(df2[1],df2[2], xscale=:log10, yscale=:log10)
scatter!(df1[1],df1[2], xscale=:log10, yscale=:log10)
# xaxis!("t",:log10)
# yaxis!("N",:log10)
