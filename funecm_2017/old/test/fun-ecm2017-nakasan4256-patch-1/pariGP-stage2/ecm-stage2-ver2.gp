ecm(N, B1,B2, nb = 100)=
{
  local(k,Ell,Q0,D,Js,Mmin,Mmax,Prime_table,q); \\関数ecm内でのみ用いる変数
  k=lcm(2,3);
  for(o=4,B1,k=lcm(o,k)); \\kは2~B1の最小公倍数
  D=210;
  Js=vector(D/2);
  GCD_table=vector(D/2);
  i=1;
  for(j=1,D/2,
    if(gcd(j,D)==1,
      GCD_table[j]=1;
      Js[i]=j;
      i++;
    );
  );
  for(j=i,D/2,Js[j]=1;);

  Mmin=((B1+D/2+1)-(B1+D/2+1)%D)/D;
  Mmax=((B2+D/2-1)-(B2+D/2-1)%D)/D;
  Prime_table=matrix(Mmax,D/2);
  for(m=Mmin,Mmax,
    for(j=1,D/2,
      if(B1<m*D+j,
        Prime_table[m,j]=isprime(m*D+j)+isprime(m*D-j);,Prime_table[m,j]=0;
      );
    );
  );

  for(a = 1, nb, \\楕円曲線の係数aをnbまでまわす

    print("stage1: a= ",a);
    Ell=ellinit([a,1]*Mod(1,N)); \\楕円曲線y^2=x^3+a*x+1

    iferr(Q0=ellmul(Ell, [0,1]*Mod(1,N), k),\\k倍した点kPをとっておく
    E,return(gcd(lift(component(E,2)),N)),
    errname(E)=="e_INV" && type(component(E,2)) == "t_INTMOD");\\ステージ1


    print("stage2: a= ",a);

    Q=Q0;
    T=ellmul(Ell,Q0,2);
    S=matrix(D/2,2);
    forstep(j=1,D/2,2,
      if(GCD_table[j]==1,
      S[j,]=Q;
      );
      Q=elladd(Ell,Q,T);
    );

    d=1;
    Q=ellmul(Ell,Q0,D);
    R=ellmul(Ell,Q,Mmin);
    for(m=Mmin,Mmax,
      for(l=1,i,
        if(Prime_table[m,Js[l]]>0,
          d=d*(S[Js[l],1]-R[1]);
        );
      );
      R=elladd(Ell,R,Q);
    );
    q=lift(gcd(d,N));
    if(q>1,return(q));
  );
