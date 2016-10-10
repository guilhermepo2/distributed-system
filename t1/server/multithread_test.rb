requisition = "curl -X GET \"http://127.0.0.1:8000/arq1\";"

threads = 10

def do_requisition
  exec requisition
end

exec requisition

for i in 0..threads
  puts i
  Thread.new{do_requisition()}
end
