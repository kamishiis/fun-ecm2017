ecm(N, B1,B2, nb = 100)=
{
  local(k,Ell,Q0,D,Js,Mmin,Mmax,q); \\関数ecm内でのみ用いる変数
  k=lcm(2,3);
  for(o=4,B1,k=lcm(o,k)); \\kは2~B1の最小公倍数
  D=210; \\210=2*3*5*7
  Js=vector(53);
  GCD_table=vector(53);
  count_gcd=1;
  forstep(j=1,D/2,2,
    if(gcd(j,D)==1,
      GCD_table[(j+1)/2]=1;
      Js[count_gcd]=j;
      count_gcd++;
    );
  );
  for(j=count_gcd,D/4,Js[j]=1;);

  Mmin=((B1+D/2+1)-(B1+D/2+1)%D)/D;
  Mmax=((B2+D/2-1)-(B2+D/2-1)%D)/D;
  Prime_table=matrix(Mmax,D/2);
  for(m=Mmin,Mmax,
    forstep(j=1,D/2,2,
      if(B1<m*D+j&&m*D-j<B2,
        Prime_table[m,j]=isprime(m*D+j)+isprime(m*D-j);
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
    T=ellmul(Ell,Q0,2); \\T=2*Q0
    S=matrix(D/2,2);
    forstep(j=1,D/2,2,
      if(GCD_table[(j+1)/2]==1, \\jが210と互いに素なら
      S[j,]=Q; \\配列Sに座標Ｑを格納
      );
      Q=elladd(Ell,Q,T); \\Q=Q+T
    );

    d=1;
    Q=ellmul(Ell,Q0,D); \\Q=210*Q0
    R=ellmul(Ell,Q,Mmin); \\R=Mmin*Q
    for(m=Mmin,Mmax,
      for(j=1,count_gcd,\\mD+-Js[j](Jsは210と互いに素)のmとJsをまわす
        if(Prime_table[m,Js[j]]>0,\\mD+Js[j]とmD-Js[j]のどちらかでも素数ならば
          d=d*(S[Js[j],1]-R[1]); \\d=d*(x座標の引き算)
        );
      );
      R=elladd(Ell,R,Q);\\R=R+Q, giant_stepを進める
    );
    q=lift(gcd(d,N));
    if(q>1,return(q)); \\うまくいけば素因数qを出力

  );
