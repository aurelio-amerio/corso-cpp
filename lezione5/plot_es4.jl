using DataFrames
using CSV
using Plots
#%%
file = open("./lezione5/Si_data.csv")
df=CSV.read(file, header=false)

plot(df[1],df[2])
