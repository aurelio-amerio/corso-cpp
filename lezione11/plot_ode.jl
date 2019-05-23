using DataFrames
using CSV
using Plots
#%%
data = open("orbit.dat")



df=CSV.read(data, header=false, delim=" ")


#%%
plot(df[1],df[2], label="orbita circolare", dpi=600)

# xaxis!(:log10)
# yaxis!(:log10)
