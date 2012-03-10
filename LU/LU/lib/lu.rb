class WrongMatrixDimentionsException < StandardError; end

class LU
  def initialize (stream)
    @matrix = Array.new
    stream.each { |line| tmp = Array.new; line.scan(/\w+/) {|match| tmp.push(match.to_f)}; @matrix.push(tmp);}
    raise WrongMatrixDimentionsException unless allok?    
  end

  def allok?
    return @matrix.find_all { |obj| obj.length == @matrix.length+1}.length==@matrix.length
  end

  def solve
    lu = Array.new(@matrix.length).map { Array.new(@matrix.length).map {0.0}}
    lu.each_index { |index| lu[0][index] = @matrix[0][index]}
    lu.each_index { |index| lu[index][0] = @matrix[index][0]/lu[0][0] if index>0}
    lu.each_index { |i|
      lu[i].each_index{|j|
        if j>=i
          tmp = 0
          lu.each_index{ |k| tmp+=lu[i][k]*lu[k][j] if k<i}
          lu[i][j]=@matrix[i][j]-tmp;       
        end}
      
        lu[i].each_index{|j|
        if j>i
          tmp = 0
          lu.each_index{ |k| tmp+=lu[j][k]*lu[k][i] if k<i}
          lu[j][i]=(@matrix[j][i]-tmp)/lu[i][i];
        end


      }
    }
    print_matrix (lu)
   

  end

  def print_matrix (matrix)
    matrix.each { |item| item.each { |i| print i, " "}; puts}
  end

end

lu = LU.new(File.open("test.in", "r"))
lu.solve