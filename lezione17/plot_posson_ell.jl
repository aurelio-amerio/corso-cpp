using DataFrames
using CSV
using Plots
#%%
data_jacobi = open("jacobi_p.dat")
df_jacobi=CSV.read(data_jacobi, header=false, delim=" ")
x_jacobi=df_jacobi[1]
y_jacobi=df_jacobi[2]
z_jacobi=reshape(df_jacobi[3],(100,100))

data_gs = open("gauss_seidel_p.dat")
df_gs=CSV.read(data_gs, header=false, delim=" ")
x_gs=df_gs[1]
y_gs=df_gs[2]
z_gs=reshape(df_gs[3],(100,100))

data_s = open("sor_p.dat")
df_s=CSV.read(data_s, header=false, delim=" ")
x_s=df_s[1]
y_s=df_s[2]
z_s=reshape(df_s[3],(101,101))


data_sol = open("sol_p.dat")
df_sol=CSV.read(data_sol, header=false, delim=" ")
x_sol=df_sol[1]
y_sol=df_sol[2]
z_sol=reshape(df_sol[3],(101,101))

x=y_sol[1:100]
y=x
#%%
plot(x,y,z_jacobi, fill=true, label="jacobi")
xlabel!("x")
ylabel!("y")
title!("jacobi")
plot!(dpi=600)
savefig("jacobi_p.png")
# xaxis!(:log10)
# yaxis!(:log10)
#%%

plot(x,y,z_gs, fill=true, label="gauss_seidel")
xlabel!("x")
ylabel!("y")
title!("gauss seidel")
plot!(dpi=600)
savefig("gs_p.png")

#%%

plot(x,y,z_s, fill=true, label="sor")
xlabel!("x")
ylabel!("y")
title!("sor")
plot!(dpi=600)
savefig("sor_p.png")
