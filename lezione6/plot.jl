using DataFrames
using CSV
using Plots
#%%
file = open("./lezione6/random.dat")
df=CSV.read(file, header=false, delim=" ")

scatter(df[1],df[2])
