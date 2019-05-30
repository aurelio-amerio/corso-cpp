using DataFrames
using CSV
using Plots
#%%
data_k1 = open("wave1.dat")
df_k1=CSV.read(data_k1, header=false, delim=" ")
r_k1=df_k1[1]
phi_k1=df_k1[2]

data_k2 = open("wave2.dat")
df_k2=CSV.read(data_k2, header=false, delim=" ")
r_k2=df_k2[1]
phi_k2=df_k2[2]

data_k3 = open("wave3.dat")
df_k3=CSV.read(data_k3, header=false, delim=" ")
r_k3=df_k3[1]
phi_k3=df_k3[2]

data_k4 = open("wave4.dat")
df_k4=CSV.read(data_k4, header=false, delim=" ")
r_k4=df_k4[1]
phi_k4=df_k4[2]


#%%
plot(df_k1[1], df_k1[2], label="k 1", dpi=600)
plot!(df_k2[1], df_k2[2], label="k 2", dpi=600)
plot!(df_k3[1], df_k3[2], label="k 3", dpi=600)
plot!(df_k4[1], df_k4[2], label="k 4", dpi=600)
plot!(grid=true, legend=:topleft)
xlabel!("r")
ylabel!("phi")
savefig("wave.png")
# xaxis!(:log10)
# yaxis!(:log10)
