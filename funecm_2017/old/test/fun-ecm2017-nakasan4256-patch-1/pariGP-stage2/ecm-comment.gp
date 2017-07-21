ecm(N, B1,B2, nb = 100)=
{
  local(k,p,s,U,r,v,v2,u,d,Gx,Hx,G,R,Ell,kP); \\関数ecm内でのみ用いる変数
  r=210;
  k=lcm(2,3);
  for(i=4,B1,k=lcm(i,k)); \\kは2~B1の最小公倍数

  for(a = 1, nb, \\楕円曲線の係数aをnbまでまわす

    print("stage1: a= ",a);
    Ell=ellinit([a,1]*Mod(1,N)); \\楕円曲線y^2=x^3+a*x+1

    iferr(kP=ellmul(Ell, [0,1]*Mod(1,N), k),\\k倍した点kPをとっておく
    E,return(gcd(lift(component(E,2)),N)),
    errname(E)=="e_INV" && type(component(E,2)) == "t_INTMOD");\\ステージ1


    print("stage2: a= ",a);
    /*rと互いに素なr以下の数iについて、U[i]=(i-1)*kPとなる配列Uを用意
    pariGPだと配列が1から始まるため*/
    U=matrix(53,2);

    for(i=1,53,
      if(gcd(r,i)>1,
        U[i,]=ellmul(Ell,kP,i),U[i,]=[0,0]*Mod(1,N)
      );
    );
    /*B1~B2内の素数sを、s=rv+u
    (r=210,vはs/rの商,tはs/rの余り)と表す*/
    s=nextprime(B1+1);
    v=(B1+r/2-(B1+r/2)%r)/r;
    v2=v; \\vのコピー、計算量節約のため
    R=ellmul(Ell,kP,r); \\R=r*kP
    G=ellmul(Ell,R,v2); \\G=v*R
    d=1;

    while(s<B2,
      v=(s-(v-r/2)%r)/r+r/2;\\giant-step
      while(v>v2,
      print("aa");
      G=elladd(Ell,G,R);
      v2++;
      ); \\giant-stepが異なるときだけG+R
      u=s-rv; \\baby-step

  \\点G,Hのx座標を取り出す(このへん工夫できそう)
      Gx=G[1];
      Hx=U[(abs(u)+1)/2,1];
      print("bb");
      d=d*(Gx-Hx);\\かけ合わせる

      s=nextprime(s+1);\\sを次の素数に
    );
    p=lift(gcd(d,N));
    if(p>1,return(p));\\うまくいけば素因数を出力
  );
}
