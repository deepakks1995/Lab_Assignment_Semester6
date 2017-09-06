function [trainData, testData] = datasets_perceptron(path)  
    % path can be LS_Group12/
    
    command = ['ls',' ',path,' -l| grep Class | wc -l'];
    [~,output] = system(command);
    numOfClasses = str2double(output)
    trainData = cell(1,numOfClasses);
    testData = cell(1,numOfClasses);
    
    dirpath = (strcat(path,'*.txt'));
    Files=dir(dirpath);
   % system('mkdir Training');
   % system('mkdir Testing');;
        
    for i=1:length(Files)
        fileName=Files(i).name;
        inputData = load([path, fileName]);
        rows = size(inputData,1);
        trainData{i} =  inputData(1:floor((3/4)* rows),:);
        testData{i} = inputData(floor((3/4)*rows)+1:end,:);
    end

    % size(trainData{1})
    % size(testData{1})

end
