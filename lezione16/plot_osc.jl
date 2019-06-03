using DataFrames
using CSV
using Plots
#%%
data_k1 = open("qho_res.dat")
df_k1=CSV.read(data_k1, header=false, delim=" ")
r_k1=df_k1[1]
phi_k1=df_k1[2]


#%%
plot(df_k1[1], df_k1[2], label="res", dpi=600)
plot!(grid=true, legend=:topleft)
xlabel!("E")
ylabel!("residual")
savefig("res.png")
# xaxis!(:log10)
# yaxis!(:log10)
