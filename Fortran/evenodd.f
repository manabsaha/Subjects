      write(*,10)
   10 format("Enter a number")
      read(*,*) inum
      IF (mod(inum,2).EQ.0) THEN
      WRITE(*,30)
   30 format('Even')
      ELSE
      write(*,40)
   40 format('Odd')
      END IF
      stop 
      end
