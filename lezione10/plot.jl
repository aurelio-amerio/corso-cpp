using DataFrames
using CSV
using Plots
#%%
bp = open("backward.dat")
fp = open("forward.dat")
cp = open("central.dat")
bp_df=CSV.read(bp, header=false, delim=" ")

plot(bp_df[1],bp_df[2])
xaxis!(:log10)
yaxis!(:log10)
