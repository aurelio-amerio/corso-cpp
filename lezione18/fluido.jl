using DataFrames
using CSV
using Plots
#%%
data_s = open("sor_fluido.dat")
df_s=CSV.read(data_s, header=false, delim=" ")
x_s=df_s[1]
y_s=df_s[2]
z_s=transpose(reshape(df_s[3],(129, 65)))
x=range(0,stop=2,length=129)
y=range(0,stop=1,length=65)
#%%

plot(x,y,z_s, fill=true, label="sor")
xlabel!("x")
ylabel!("y")
title!("sor")
plot!(dpi=600)
savefig("sor_fluido.png")
