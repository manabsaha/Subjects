      write(*,10)
   10 format(0X,"Enter two numbers")
      read(*,20) fnum1
      read(*,20) fnum2
   20 format(F10.3)
      fsum=fnum1+fnum2
      fdiff=fnum1-fnum2
      fprod=fnum1*fnum2
      fdiv=fnum1/fnum2
      fmod=mod(fnum1,fnum2)
      fsqrt=sqrt(12.0)
      write(*,30) fsum,fdiff,fprod,fdiv,fmod,fsqrt
   30 format(7F10.3)
      stop
      end
