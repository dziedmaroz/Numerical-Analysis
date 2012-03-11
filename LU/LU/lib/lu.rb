#!/usr/bin/env ruby
class NilMatrixExcpetion < StandardError; end
class WrongMatrixDimentionsException < StandardError; end
class NoArgsException < StandardError; end
class DivByZeroException < StandardError; end

class LU
  def initialize (stream)    
    @matrix = Array.new
    stream.each { |line| tmp = Array.new; line.scan(/-?\d+/) {|match| tmp.push(match.to_f)}; @matrix.push(tmp);}
    raise NilMatrixExcpetion unless @matrix.length!=0
    raise WrongMatrixDimentionsException unless allok?
  end

  def allok?
    return @matrix.find_all { |obj| obj.length == @matrix.length+1}.length==@matrix.length
  end

  def solve
    l = Array.new(@matrix.length).map{Array.new}
    u = Array.new(@matrix.length).map{Array.new}
    @matrix.each_index { |i| u[0].push(@matrix[0][i])}
    raise DivByZeroException unless u[0][0]!=0
    @matrix.each_index {|i| l[i].push(@matrix[i][0]/u[0][0])}
    @matrix.each_index {|i|
      if i>0
        @matrix.each_index { |j|
          if j>=i
            tmp = 0
            for k in 0 .. i-1
              tmp +=l[i][k]*u[k][j]
            end
            u[i][j]=@matrix[i][j]-tmp;
          end
        }
        @matrix.each_index { |j|
          if j>=i+1
            tmp = 0
            for k in 0..i-1
              tmp+=l[j][k]*u[k][i]
            end
            l[j][i] =(@matrix[j][i]-tmp)/u[i][i];
            raise DivByZeroException unless u[i][i]!=0
          end
        }
        l[i][i]=1.0;
      end
    }
    y = Array.new(@matrix.length);
    y.each_index {|i|
      tmp = 0
      l[i].each_index { |j| tmp+=l[i][j]*y[j] if j<i }
      y[i]=@matrix[i].last-tmp
    }
    x = Array.new(@matrix.length)
    x.each_index { |i|
      tmp = 0 ;
      u[u.length-1-i].each_index { |j| tmp+=u[u.length-1-i][j]*x[j] if j>u.length-1-i }
      x[x.length-1-i] = (y[x.length-1-i]-tmp)/u[u.length-1-i][u.length-1-i];
    }
   return x;
  end
end

raise NoArgsException unless ARGV.first!=nil
lu = LU.new(File.open(ARGV.first, "r"))
fout = File.open(ARGV.first.gsub(/\.in/, ".out"),"w")
lu.solve.each { |e| fout<<sprintf("%3.3f",e)<<" "}
