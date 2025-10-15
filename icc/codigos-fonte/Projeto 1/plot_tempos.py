import sys
import pandas as pd
import matplotlib.pyplot as plt

if len(sys.argv) < 2:
    print("Uso: python3 plot_tempos.py <tempos.csv>")
    raise SystemExit(1)

df = pd.read_csv(sys.argv[1])
df_num = df[pd.to_numeric(df['time_ms'], errors='coerce').notnull()].copy()
df_num['time_ms'] = df_num['time_ms'].astype(float)

pivot = df_num.pivot_table(index='n', columns='method', values='time_ms', aggfunc='mean')

ax = pivot.plot(marker='o')
ax.set_xlabel('n (número de itens)')
ax.set_ylabel('tempo (ms)')
ax.set_title('Mochila 0/1 — tempos por método (seu código)')
ax.grid(True)

plt.tight_layout()
plt.savefig('tempos.png', dpi=160)
print("Gráfico salvo em tempos.png")
