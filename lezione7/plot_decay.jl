using DataFrames
using CSV
using Plots
#% %
file1 = open("rand_decay.dat")
file2 = open("exp_decay.dat")
df1=CSV.read(file1, header=false, delim=" ")
df2=CSV.read(file2, header=false, delim=" ")
#%%
plot(df2[1],df2[2], title="radioactive decay")
scatter!(df1[1],df1[2], markersize=2)
xaxis!("t", xlims=(1,Inf))
yaxis!("N", ylims=(1,Inf), yscale= :log10)
