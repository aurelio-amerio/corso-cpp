# Roundoff

Problema: se io ho una formula del tipo 
$$
\sqrt{x^2+1}-x
$$
per x->inf crea problemi

### Soluzione 1

Posso ad esempio razionalizzare in moda da non avere più una sottrazione:
$$
\sqrt{x^2+1}-x=(\sqrt{x^2+1}-x)\frac{\sqrt{x^2+1}+x}{\sqrt{x^2+1}+x} = \frac{x^2+1-x^2}{\sqrt{x^2+1}+x}=\frac{1}{\sqrt{x^2+1}+x}
$$


```

```

In questo modo non c'è più una sottrazione catastrofica.

### Soluzione 2

Un'altra soluzione consiste nell'utilizzare una serie di Taylor
$$
\sqrt{x^2+1}= x\sqrt{1+\frac{1}{x^2}}\approx x(1+\frac{1}{2x^2}) \\
\sqrt{x^2+1}-x \approx \frac{1}{2x}
$$
