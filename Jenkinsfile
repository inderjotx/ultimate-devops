pipeline {

	agent any 

		tools {

			nodejs "node"

		}

	environment {
		DOCKER-CRED = credentials('docker-credentials')
			API_KEY = credentials('api-key')
			TAG = sh(date +%s)
			IMAGE = inderharrysingh/ultimate:$TAG

	}


	stages {


		stage('Installing'){

			steps {
				sh 'echo "Starting Installation...."'
					sh 'npm install'	
			}

		}

		stage('Testing'){

			steps{

				sh 'echo "Mock testing..."'
			}

		}

		stage('Testing Filesystem'){

			steps {

				sh 'trivy fs . '

			}

		}


		stage('Building Docker Image'){


			steps {


				docker build . -t $IMAGE --build-args=TMDB_V3_API_KEY=$API_KEY

			}

		}


		stage('Testing Built Image'){

			steps {

				trivy image $IMAGE
			}
		}



		stage('Pushing Created Image'){

			steps{
				
 	  			script {
							
						withCredentials([string(credentialsId: DOCKER_CRED , variable: 'DOCKER_HUB_PASSWORD')]) {
                        			sh "echo $DOCKER_HUB_PASSWORD | docker login -u inderharrysingh --password-stdin"
                   	

					
						docker push $IMAGE
				 }


}
				
			}

		}



	}





post {

	always {

		docker rmi $IMAGE
}

}






}
